#!/usr/bin/python3
import socket
import ctypes
import time
import logging
from random import randint
from Lsr import LsrProtocolParser

HOST = '127.0.0.1'
PORT = 12345

FREQUENCY = 50 #high frequency
#FREQUENCY = 10 #low frequency

def run_server(host, port):
	lsr_parser = LsrProtocolParser()
	with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
		s.bind((host, port))
		s.listen()
		conn, addr = s.accept()
		with conn:
			logging.info('Connected by %s' % addr[0])

			header = lsr_parser.header_from_rawdata(conn.recv(lsr_parser.header_size))
			record = lsr_parser.record_from_rawdata(conn.recv(header.data_size), header.data_type)
			logging.info('PING : %s' % record)
			conn.send(lsr_parser.build_ping_packet(reference=record.value)[0])
			logging.info('Disconnected')
		conn, addr = s.accept()
		with conn:
			logging.info('Connected by %s' % addr[0])
			
			header = lsr_parser.header_from_rawdata(conn.recv(lsr_parser.header_size))
			record = lsr_parser.record_from_rawdata(conn.recv(header.data_size), header.data_type)
			logging.info('Requested recorder : %s' % record.value.decode('utf-8'))
			tick = 0
			while tick < 20:
					rand = randint(0, 10)
					conn.send(lsr_parser.build_packet(rand, tick, ctypes.c_int))
					time.sleep(1/FREQUENCY)
					tick += 1
			logging.info('Disconnected')

if __name__ == '__main__':
	logger = logging.getLogger('Lsr').setLevel(logging.DEBUG)
	run_server(HOST, PORT)
