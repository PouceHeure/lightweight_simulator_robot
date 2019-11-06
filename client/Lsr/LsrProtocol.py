#!/usr/bin/python3
import struct
import binascii
import random
from ctypes import c_byte, c_short, c_int, c_long, c_ubyte, c_ushort, c_uint, c_ulong, c_float, c_double, c_char_p
from .LsrLogger import init_logger

logger = init_logger(__name__)

class LsrProtocolRecord:
	"""Simple wrapper for LSR records (from LSR recorders)
	
	This class can wrap any property, as the record structure is not totally fixed yet.
	"""
	def __init__(self, **kwargs):
		"""Constructor for LsrProtocolRecord class
		"""
		for key in kwargs:
			setattr(self, key, kwargs[key])

	def __repr__(self):
		"""Produce the string representation of the record
		"""
		return repr(self.__dict__)

class LsrProtocolHeader:
	"""Simple wrapper for LSR protocol headers
	
	This class can wrap any property, as the header structure is not totally fixed yet.
	"""
	def __init__(self, **kwargs):
		"""Constructor for LsrProtocolHeader class
		"""
		for key in kwargs:
			setattr(self, key, kwargs[key])

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
		self.id_to_type = {0x0:None, 0x1:c_byte, 0x2:c_short, 0x3:c_int, 0x4:c_long, 0x5:c_ubyte, 0x6:c_ushort, 0x7:c_uint, 0x8:c_ulong, 0x9:c_float, 0xa:c_double, 0xb:c_char_p} #this dict is the mapping between C types and id used in the LSR protocol
		self.type_to_id = {v: k for k, v in self.id_to_type.items()} #reversed id_to_type dict, for reverse translations
		
	def build_authentication_packet(self, recorder_name):
		"""Build authentication packet from a recorder name
		"""
		return self.build_packet(recorder_name, 0, c_char_p)

	def build_ping_packet(self, reference = None):
		"""Build ping packet or build answer to ping packet
		"""
		if reference == None:
			reference = random.randint(0x00, 0xff)
		return self.build_packet(reference, reference, c_ubyte), reference

	def check_ping_packet(self, record, reference):
		"""Verify ping packet integrity
		"""
		return record.value == reference and record.c_type == c_ubyte
	
	def build_packet(self, value, tick, c_type):
		"""Build data packet from value, tick, and ctype
		"""
		data_type = self.type_to_id[c_type]
		record = LsrProtocolRecord(tick=tick, c_type=c_type, value=value)
		raw_record = self.rawdata_from_record(record)
		header = LsrProtocolHeader(data_size=len(raw_record), data_type=data_type)
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
		type = record.c_type
		type_format = type._type_
		if type == c_char_p:
			type_format = "%ds" % len(record.value)
		raw_record = struct.pack(self.tick_format + type_format, record.tick, record.value)
		logger.debug("Encoded/Sent record : %s from %s" % (str(binascii.hexlify(raw_record)), record))
		return raw_record

	def header_from_rawdata(self, header_data):
		"""Convert raw data to LsrProtocolHeader (after receiving it from the server)
		"""
		data_type, data_size = struct.unpack(self.header_format, header_data)
		header = LsrProtocolHeader(data_size=data_size, data_type=data_type)
		logger.debug("Decoded/Received header : %s from %s" % (header, str(binascii.hexlify(header_data))))
		return header

	def record_from_rawdata(self, payload_data, data_type):
		"""Convert raw data to LsrProtocolRecord (after receiving it from the server)
		"""
		type = self.id_to_type[data_type]
		type_format = type._type_
		if type == c_char_p:
			type_format = "%ds" % (len(payload_data) - self.tick_size)
		tick, value = struct.unpack(self.tick_format + type_format, payload_data)
		record = LsrProtocolRecord(tick=tick, c_type=type, value=value)
		logger.debug("Decoded/Received record : %s from %s" % (record, str(binascii.hexlify(payload_data))))
		return record
