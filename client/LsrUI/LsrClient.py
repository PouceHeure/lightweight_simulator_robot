#!/usr/bin/python3
import socket
import sys
import logging
from .LsrProtocol import LsrProtocolParser

class LsrClient:
	"""Client interface with the LSR server
	
	This class implements all the communications/network level interactions with the LSR server.
	"""

	def __init__(self, _host, _port, _recorder_name, _timeout = 1):
		"""Constructor for LsrClient class
		
		You need at least host, port and recorder name to interact with the server.
		Timeout (in seconds) can be modified if you are in a laggy network for example.
		"""
		self.host = _host
		self.port = _port
		self.recorder_name = _recorder_name
		self.timeout = _timeout
		self.socket = None
		self.lsr_parser = LsrProtocolParser()

	def connect(self):
		"""Open connection to the remote LSR server and authenticate to a recorder
		"""
		self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		self.socket.connect((self.host, self.port))
		auth_packet = self.lsr_parser.build_authentication_packet(self.recorder_name)
		self.socket.send(auth_packet)

	def get_record(self):
		"""Get a record from the choosen recorder on the server
		"""
		try:
			self.socket.settimeout(self.timeout)
			header_data = self.socket.recv(self.lsr_parser.header_size)
			parsed_header = self.lsr_parser.header_from_rawdata(header_data)
			self.socket.settimeout(self.timeout)
			payload_data = self.socket.recv(parsed_header.data_size)
			record = self.lsr_parser.record_from_rawdata(payload_data, parsed_header.data_type)
			return record
		except:
			#error handling
			logging.debug(sys.exc_info()[0])
			return None
		return record
		
	def get_records(self):
		"""Get an iterator object which iterates through all the records from the choosen recorder on the server
		"""
		record = self.get_record()
		while record is not None:
			yield record
			record = self.get_record()
		return	

	def close(self):
		"""Close the connection to the remote server
		"""
		self.socket.close()
