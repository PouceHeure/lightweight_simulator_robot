#!/usr/bin/python3
import struct
import binascii
import random
from .LsrTypes import LsrPing, LsrByte, LsrShort, LsrInt, LsrLong, LsrUByte, LsrUShort, LsrUInt, LsrULong, LsrFloat, LsrDouble, LsrString
from .LsrLogger import init_logger

logger = init_logger(__name__)

class LsrProtocolRecord:
	"""Simple wrapper for LSR records (from LSR recorders)
	
	This class can wrap any property, as the record structure is not totally fixed yet.
	"""
	def __init__(self, _tick, _type, _values):
		"""Constructor for LsrProtocolRecord class
		"""
		self.tick = _tick
		self.type = _type
		self.values = _values

	def __repr__(self):
		"""Produce the string representation of the record
		"""
		return repr(self.__dict__)

class LsrProtocolHeader:
	"""Simple wrapper for LSR protocol headers
	
	This class can wrap any property, as the header structure is not totally fixed yet.
	"""
	def __init__(self, _data_size, _data_type):
		"""Constructor for LsrProtocolHeader class
		"""
		self.data_size = _data_size
		self.data_type = _data_type

	def __repr__(self):
		"""Produce the string representation of the header
		"""
		return repr(self.__dict__)

class LsrProtocolParser:
	def __init__(self):
		"""Constructor for LstProtocolParser class

		Initialize the protocol parser from hardcoded definitions.
		"""
		self.init_protocol_definitions()

	def init_types(self):
		"""Init default hardcoded LSR types to id bindings
		"""
		id_to_type = {}
		id_to_type[0x0] = LsrPing
		id_to_type[0x1] = LsrByte
		id_to_type[0x2] = LsrShort
		id_to_type[0x3] = LsrInt
		id_to_type[0x4] = LsrLong
		id_to_type[0x5] = LsrUByte
		id_to_type[0x6] = LsrUShort
		id_to_type[0x7] = LsrUInt
		id_to_type[0x8] = LsrULong
		id_to_type[0x9] = LsrFloat
		id_to_type[0xa] = LsrDouble
		id_to_type[0xb] = LsrString
		return id_to_type

	def init_protocol_definitions(self):
		"""Init default hardcoded LSR protocol definitions
		"""
		self.data_type_format = "H" #unsigned short
		self.data_type_size = 2 #unsigned short size
		self.data_length_format = "H" #unsigned short
		self.data_length_size = 2 #unsigned short size
		self.header_format = self.data_type_format + self.data_length_format #header = data_type || data_size
		self.header_size = self.data_type_size + self.data_length_size #header = data_type || data_size
		self.tick_format = "I" #unsigned int
		self.tick_size = 4 #unsigned int size
		self.id_to_type = self.init_types() #this dict is the mapping between types and id used in the LSR protocol
		self.type_to_id = {v: k for k, v in self.id_to_type.items()} #reversed id_to_type dict, for reverse translations
		
	def build_authentication_packet(self, recorder_name):
		"""Build authentication packet from a recorder name
		"""
		return self.build_packet((recorder_name,), 0, LsrString)

	def build_ping_packet(self, reference = None):
		"""Build ping packet or build answer to ping packet
		"""
		if reference == None:
			reference = random.randint(0x00, 0xff)
		return self.build_packet((reference,), reference, LsrPing), reference

	def check_ping_packet(self, record, reference):
		"""Verify ping packet integrity
		"""
		return record.value == reference and record.type == LsrPing
	
	def build_packet(self, values, tick, type):
		"""Build data packet from value, tick, and ctype
		"""
		data_type = self.type_to_id[type]
		record = LsrProtocolRecord(tick, type, values)
		raw_record = self.rawdata_from_record(record)
		header = LsrProtocolHeader(len(raw_record), data_type)
		raw_header = self.rawdata_from_header(header)
		packet = raw_header + raw_record
		return packet
		
	def rawdata_from_header(self, header):
		"""Convert LsrProtocolHeader to raw data (before sending it to server)
		"""
		raw_header = struct.pack(self.header_format, header.data_type, header.data_size)
		logger.debug("Encoded/Sent header : %s from %s" % (str(binascii.hexlify(raw_header)), header))
		return raw_header

	def rawdata_from_record(self, record):
		"""Convert LsrProtocolRecord to raw data (before sending it to server)
		"""
		type = record.type
		type_format = type.format
		if type == LsrString:
			type_format = type_format % (len(record.values[0]))
		else:
			type_format = type_format % (len(record.values))
		raw_record = struct.pack(self.tick_format + type_format, record.tick, *record.values)
		logger.debug("Encoded/Sent record : %s from %s" % (str(binascii.hexlify(raw_record)), record))
		return raw_record

	def header_from_rawdata(self, header_data):
		"""Convert raw data to LsrProtocolHeader (after receiving it from the server)
		"""
		data_type, data_size = struct.unpack(self.header_format, header_data)
		header = LsrProtocolHeader(data_size, data_type)
		logger.debug("Decoded/Received header : %s from %s" % (header, str(binascii.hexlify(header_data))))
		return header

	def record_from_rawdata(self, payload_data, data_type):
		"""Convert raw data to LsrProtocolRecord (after receiving it from the server)
		"""
		type = self.id_to_type[data_type]
		type_format = type.format
		type_format = type_format % ((len(payload_data) - self.tick_size) / type.byte_length)
		out = struct.unpack(self.tick_format + type_format, payload_data)
		tick = out[0]
		values = out[1:]
		record = LsrProtocolRecord(tick, type, values)
		logger.debug("Decoded/Received record : %s from %s" % (record, str(binascii.hexlify(payload_data))))
		return record
