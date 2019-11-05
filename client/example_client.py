#!/usr/bin/python3
import logging
import warnings
import matplotlib.pyplot as plt
import argparse
from math import sqrt, ceil
from Lsr import LsrClient

def init_graph(recorders):
	fig = plt.figure()
	col_num = ceil(sqrt(len(recorders)))
	layout = col_num * 110
	axes = []
	for i in range(1, len(recorders) + 1):
		axes.append(fig.add_subplot(layout + i))
		axes[-1].title.set_text(recorders[i - 1])
	return axes

def live_plot(record, graph, num_packet):
	for value in record.values:
		graph.plot(record.tick, value, '.')
		graph.lines = graph.lines[-num_packet:]
		graph.set_xbound(lower=graph.lines[0].get_xdata()[0], upper=graph.lines[-1].get_xdata()[0])

def run_client(host, port, recorders):
	lsr = LsrClient(host, port)
	graphs = init_graph(recorders)

	for i in range(len(recorders)):
		lsr.add_recorder(recorders[i])
		lsr.bind(recorders[i], live_plot, {"graph" : graphs[i], "num_packet" : 400})

	lsr.run_background()

	while lsr.is_running():
		plt.pause(0.001)
	
	lsr.finish()
	plt.pause(10)

def init_args():
	parser = argparse.ArgumentParser(description='LSR Client || 0xUKN & PoussPouss')
	parser.add_argument('h', help='Lsr Server Hostname/IP')
	parser.add_argument('p', help='Lsr Server port', type=int)
	parser.add_argument('-f', help='Recorders file', default="recorders.list")
	args = parser.parse_args()
	out = [args.h, args.p]
	with open(args.f, 'r') as file:
		recorders = file.read().splitlines()
		recorders = list(filter(None, recorders))
	out.append(recorders)
	return out

if __name__ == '__main__':
	warnings.filterwarnings("ignore", module="matplotlib")
	logging.getLogger('Lsr').setLevel(logging.INFO)
	
	args = init_args()

	run_client(*args)
	exit(0)




