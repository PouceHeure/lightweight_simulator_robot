#!/usr/bin/python3
import logging
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style
from LsrUI.LsrClient import LsrClient
import sys

HOST = '192.168.43.75'
PORT = 12345
RECORDER_NAME = "r_test_float".encode('utf-8') #sys.argv[1].encode('utf-8')

def live_plot(records, graph_max_size = 40):
	x = []
	y = []
	record = next(records, None)
	for record in records:
		logging.info("Received : %s" % record)
		#x.append(record.tick)
		#y.append(record.value)
		#plt.cla()
		#x = x[-graph_max_size:]
		#y = y[-graph_max_size:]
		#plt.plot(x, y, '-o')
		plt.plot(record.tick, record.value, 'o')
		plt.pause(0.01)
	
if __name__ == '__main__':
	logging.basicConfig(format='[%(levelname)s] %(message)s', level=logging.DEBUG) #level = logging.INFO
	lsr = LsrClient(HOST, PORT, RECORDER_NAME)
	lsr.connect()
	logging.info("Connected to %s:%d" % (HOST, PORT))

	records = lsr.get_records()

	plt.style.use('ggplot')
	live_plot(records)
	plt.show()
	
	lsr.close()
	logging.info("Disconnected !")
