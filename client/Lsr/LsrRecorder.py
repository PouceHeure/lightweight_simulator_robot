#!/usr/bin/python3
from .LsrLogger import init_logger

logger = init_logger(__name__)

class LsrRecorder:
	"""Recorder class : contains a socket to the server and some callbacks
	
	This class implements all the communications/network level interactions with the LSR server.
	"""

	def __init__(self, _name, _socket):
		"""Constructor for LsrRecorder class
	
		You need a recorder name and a socket to build a recorder
		"""
		self.name = _name
		self.socket = _socket
		self.callbacks = [] #_callbacks = [(callback, kwargs), (callback, kwargs), ...]

	def add_callback(self, callback_function, args):
		"""Add a callback to the specified recorder (function first, and then arguments as a dict)
		
		The record argument is internal only, and can be ignored by the user
		"""
		self.callbacks.append((callback_function, args))
	
	def call_callbacks(self, record):
		for callback in self.callbacks:
			func = callback[0]
			args = callback[1]
			args["record"] = record
			func(**args)
			args.pop("record") #delete record from args
