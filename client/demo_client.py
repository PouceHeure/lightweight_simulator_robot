#!/usr/bin/python3
import logging
import matplotlib.pyplot as plt
from Lsr import LsrClient

HOST = '127.0.0.1'
PORT = 12345
RECORDER_NAME_A = "r_test_float".encode('utf-8')
RECORDER_NAME_B = "r_test_int".encode('utf-8')

def live_plot(record, graph):
	graph.plot(record.tick, record.value, 'r.')
	
if __name__ == '__main__':
	logger = logging.getLogger('Lsr').setLevel(logging.DEBUG)

	fig = plt.figure()
	ax1 = fig.add_subplot(221)
	ax2 = fig.add_subplot(222)
	ax1.title.set_text('Test Float')
	ax2.title.set_text('Test Int')

	lsr = LsrClient(HOST, PORT)

	lsr.add_recorder(RECORDER_NAME_A)
	lsr.add_recorder(RECORDER_NAME_B)

	lsr.bind(RECORDER_NAME_A, live_plot, {"graph" : ax1})
	lsr.bind(RECORDER_NAME_B, live_plot, {"graph" : ax2})

	lsr.run_background()

	while lsr.is_running:
		plt.pause(0.01)
		plt.show()
	
	lsr.finish()
	plt.show()


