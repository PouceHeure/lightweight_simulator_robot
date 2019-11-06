#!/usr/bin/python3
import logging
import matplotlib.pyplot as plt
from Lsr import LsrClient

HOST = '127.0.0.1'
PORT = 12345
RECORDER_NAME_A = b"r_test_float"
RECORDER_NAME_B = b"r_test_int"

def live_plot(record, graph):
	graph.plot(record.tick, record.value, 'o')
	
if __name__ == '__main__':
	logger = logging.getLogger('Lsr').setLevel(logging.DEBUG)
	lsr = LsrClient(HOST, PORT)
	lsr.add_recorder(RECORDER_NAME_A)
	lsr.add_recorder(RECORDER_NAME_B)

	fig = plt.figure()
	ax1 = fig.add_subplot(221)
	ax2 = fig.add_subplot(222)
	ax1.title.set_text('Test Float')
	ax2.title.set_text('Test Int')

	lsr.bind(RECORDER_NAME_A, live_plot, {"graph":ax1})
	lsr.bind(RECORDER_NAME_B, live_plot, {"graph":ax2})
	
	lsr.finish()
	plt.show()


"""
fig, axs = plt.subplots(2)
fig.suptitle('Vertically stacked subplots')
axs[0].plot(x, y)
axs[1].plot(x, -y)
"""
"""
fig = plt.figure()
ax1 = fig.add_subplot(221)
ax2 = fig.add_subplot(222)
ax3 = fig.add_subplot(223)
ax4 = fig.add_subplot(224)
ax1.title.set_text('First Plot')
ax2.title.set_text('Second Plot')
ax3.title.set_text('Third Plot')
ax4.title.set_text('Fourth Plot')
plt.show()
"""
