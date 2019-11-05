#!/usr/bin/python3
import logging

def init_logger(name):
	logging.basicConfig(format='[%(name)s::%(levelname)s] %(message)s', level=logging.INFO)
	logger = logging.getLogger(name)
	return logger
