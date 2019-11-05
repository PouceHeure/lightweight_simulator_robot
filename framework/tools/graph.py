#! /bin/usr/python3.5

import sys
import csv
import matplotlib.pyplot as plt

def read_csv(path_file): 
    data = []
    with open(path_file, newline='') as csvfile:
       spamreader = csv.reader(csvfile, delimiter=';', quotechar='|')
       for row in spamreader:
            data.append(row)
           #print(row)
    return data 

def plot_data(data):
    x_values = []
    y_values = []
    for d in data: 
        x,y = d
        x_values.append(float(x))
        y_values.append(float(y))
    plt.plot(x_values,y_values)
    plt.xlabel('tick')
    plt.ylabel('value')
    plt.show()	


	


if __name__=="__main__":	
	data = read_csv(sys.argv[1])
	plot_data(data)

