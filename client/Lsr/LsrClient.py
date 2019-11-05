#!/usr/bin/python3
import socket
import threading
from .LsrProtocol import LsrProtocolParser
from .LsrRecorder import LsrRecorder
from .LsrLogger import init_logger

logger = init_logger(__name__)

class LsrClient:
	"""Client interface with the LSR server
	
	This class implements all the communications/network level interactions with the LSR server.
	"""

	def __init__(self, _host, _port, _timeout = 1):
		"""Constructor for LsrClient class
		
		You need at least host, port and recorder name to interact with the server.
		Timeout (in seconds) can be modified if you are in a laggy network for example.
		"""
		self.host = _host
		self.port = _port
		self.timeout = _timeout
		self.recorders = {}
		self.lsr_parser = LsrProtocolParser()
		self.is_running = False
		self.check_connection()

	def check_connection(self):
		"""Check if the remote LSR server is available
		"""
		return True #implement ping on server
		logger.info("Checking connection with %s:%d ..." % (self.host, self.port))
		with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as sock:
			sock.connect((self.host, self.port))
			ping_packet, reference = self.lsr_parser.build_ping_packet()
			sock.send(ping_packet)
			
			sock.settimeout(self.timeout)
			header_data = sock.recv(self.lsr_parser.header_size)
			parsed_header = self.lsr_parser.header_from_rawdata(header_data)
			sock.settimeout(self.timeout)
			payload_data = sock.recv(parsed_header.data_size)
			record = self.lsr_parser.record_from_rawdata(payload_data, parsed_header.data_type)

		if not self.lsr_parser.check_ping_packet(record, reference):
			raise Exception("Network error : %s:%d didn't replied to ping (request = %d, answer = %d)." % (self.host, self.port, reference, record.value))
		else:
			logger.info("Connection is OK !")

	def add_recorder(self, recorder_name):
		"""Add a recorder to the Lsr client
		"""
		logger.info("Adding recorder <%s> ..." % recorder_name.decode('utf-8'))
		sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		sock.connect((self.host, self.port))
		auth_packet = self.lsr_parser.build_authentication_packet(recorder_name)
		sock.send(auth_packet)
		self.recorders[recorder_name] = LsrRecorder(recorder_name, sock)
		if self.get_record(recorder_name) == None:
			raise Exception("Authentification failed : %s is not an available recorder." % recorder_name)
		logger.info("Successfully added recorder <%s> !" % recorder_name.decode('utf-8'))

	def get_record(self, recorder_name):
		"""Get a record from the choosen recorder on the server
		"""
		sock = self.recorders[recorder_name].socket
		try:
			sock.settimeout(self.timeout)
			header_data = sock.recv(self.lsr_parser.header_size)
			parsed_header = self.lsr_parser.header_from_rawdata(header_data)
			sock.settimeout(self.timeout)
			payload_data = sock.recv(parsed_header.data_size)
			record = self.lsr_parser.record_from_rawdata(payload_data, parsed_header.data_type)
		except Exception as e:
			logger.debug("End of transmission : socket closed or invalid packet received ...")
			logger.debug("Error : %s" % str(e))
			payload_data = ""
			header_data = ""
			parsed_header = None
			record = None
		return record
		
	def get_records(self, recorder_name):
		"""Get an iterator object which iterates through all the records from the choosen recorder on the server
		"""
		record = self.get_record(recorder_name)
		while record is not None:
			yield record
			record = self.get_record(recorder_name)
		return

	def bind(self, recorder_name, callback_function, args):
		"""Add a callback to the specified recorder (function first, and then arguments as a dict)
		
		The record argument is internal only, and can be ignored by the user
		"""
		recorder = self.recorders[recorder_name]
		recorder.add_callback(callback_function, args)

	def run_recorder(self, recorder_name):
		"""Get an iterator object which iterates through all the records from the choosen recorder on the server, and execute all the previously specified callbacks for this recorder
		"""
		recorder = self.recorders[recorder_name]
		record = self.get_record(recorder_name)
		while record is not None:
			recorder.call_callbacks(record)
			record = self.get_record(recorder_name)
		return

	def run_foreground(self):
		"""Run all recorders on several threads in foreground (blocking)
		"""
		self.is_running = True
		threads = []
		for recorder_name in self.recorders.keys(): #Build all threads
			threads.append(threading.Thread(target=self.run_recorder, args=(recorder_name,), name=recorder_name))

		for thread in threads: #Start all threads
			thread.start()

		for thread in threads: #Wait all threads to finish
			thread.join()
		self.is_running = False

	def run_background(self):
		"""Run all recorders on several threads in background (non-blocking)
		"""
		thread_root = threading.Thread(target=self.run_foreground, name=b"root")
		thread_root.daemon = True
		thread_root.start()

	def close(self, recorder_name):
		"""Close a connection to the remote server
		"""
		self.recorders[recorder_name].socket.close()
		logger.info("Disconnected recorder %s !" % recorder_name.decode('utf-8'))

	def finish(self):
		"""Close all connections to the remote server
		"""
		for recorder_name in self.recorders.keys():
			self.close(recorder_name)
		logger.info("Disconnected from %s:%d !" % (self.host, self.port))
