# Lsr Client

A Python library to interact and analyze simulation datas from the Lsr library

# Installation
1. Clone the repo from `https://github.com/PoussPouss/lightweight_simulator_robot`
2. Install the package with `python3 setup.py install`

# Usage

Simple example :
```
from Lsr import LsrClient

def callback(record, arg):
	for value in record.values:
		print("[%d] %s" % (record.tick, arg + value))

lsr = LsrClient("127.0.0.1", 12345)
lsr.add_recorder("test_recorder")
lsr.bind("test_recorder", callback, {"arg" : "Test : "})

lsr.run_background()
while lsr.is_running():
	pass
	
lsr.finish()
```

`LsrClient(<host>, <port>)` : connect to the Lsr server\
`lsr.add_recorder(<recorder_name>)` : listen to a specific recorder\
`lsr.bind(<recorder_name>, <callback function>, <callback args>)` : bind a callback function to a specific recorder\
`lsr.run_background()` : run the client\
`lsr.is_running()` : wait the client to exit\
`lsr.finish()` : close the connexion\
