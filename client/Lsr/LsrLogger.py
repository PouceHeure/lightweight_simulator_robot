#!/usr/bin/python3
import logging

def init_logger(name):
	"""Initialize Lsr logger for a module/class
	"""
	logger = logging.getLogger(name)

	sh = logging.StreamHandler()
	formatter = logging.Formatter('[%(name)s::%(levelname)s] %(message)s')
	sh.setFormatter(formatter)

	def decorate_emit(fn):
		def new(*args):
			levelno = args[0].levelno
			if(levelno >= logging.CRITICAL):
				color = '\x1b[31;1m'
			elif(levelno >= logging.ERROR):
				color = '\x1b[31;1m'
			elif(levelno >= logging.WARNING):
				color = '\x1b[34;1m'
			elif(levelno >= logging.INFO):
				color = '\x1b[32;1m'
			elif(levelno >= logging.DEBUG):
				color = '\x1b[33;1m'
			else:
				color = '\x1b[0m'
			args[0].levelname = "{0}{1}\x1b[0m".format(color, args[0].levelname)
 
			args[0].args = tuple('\x1b[1m' + arg + '\x1b[0m' for arg in args[0].args)
			return fn(*args)
		return new
	sh.emit = decorate_emit(sh.emit)
	logger.addHandler(sh)
	return logger


