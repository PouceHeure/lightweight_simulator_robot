#!/usr/bin/python3
from .LsrLogger import init_logger

logger = init_logger(__name__)

class LsrPing:
	name = "ping"
	format = "%db"
	byte_length = 1

class LsrByte:
	name = "byte"
	format = "%db"
	byte_length = 1

class LsrShort:
	name = "short"
	format = "%dh"
	byte_length = 2

class LsrInt:
	name = "int"
	format = "%di"
	byte_length = 4

class LsrLong:
	name = "long"
	format = "%dl"
	byte_length = 8

class LsrUByte:
	name = "ubyte"
	format = "%dB"
	byte_length = 1

class LsrUShort:
	name = "ushort"
	format = "%dH"
	byte_length = 2

class LsrUInt:
	name = "uint"
	format = "%dI"
	byte_length = 4

class LsrULong:
	name = "ulong"
	format = "%dL"
	byte_length = 8

class LsrFloat:
	name = "float"
	format = "%df"
	byte_length = 4

class LsrDouble:
	name = "double"
	format = "%dd"
	byte_length = 8

class LsrString:
	name = "string"
	format = "%ds"
	byte_length = 1
