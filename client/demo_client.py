#!/usr/bin/python3
import logging
import matplotlib.pyplot as plt
from Lsr import LsrClient

HOST = '127.0.0.1'
PORT = 12345
RECORDER_NAME = "r_test_float".encode('utf-8')

def live_plot(records, graph_max_size = 40):
	for record in records:
		plt.plot(record.tick, record.value, 'o')
		plt.pause(0.01)
	
if __name__ == '__main__':
	#logger = logging.getLogger('Lsr').setLevel(logging.DEBUG)
	lsr = LsrClient(HOST, PORT, RECORDER_NAME)
	lsr.connect()

	records = lsr.get_records()

	live_plot(records)
	lsr.close()
	plt.show()
