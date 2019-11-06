#!/usr/bin/python3
from .LsrLogger import init_logger

logger = init_logger(__name__)

class LsrRecorder:
	"""Recorder class : contains a socket to the server and some callbacks
	
	This class implements all the communications/network level interactions with the LSR server.
	"""

	def __init__(self, _name, _socket):
		"""Constructor for LsrRecorder class
	
		You need a recorder name and a socket to build a recorder
		"""
		self.name = _name
		self.socket = _socket
		self.callbacks = [] #_callbacks = [(callback, kwargs), (callback, kwargs), ...]

	def add_callback(self, callback_function, args):
		"""Add a callback to the specified recorder (function first, and then arguments as a dict)
		
		The record argument is internal only, and can be ignored by the user
		"""
		self.callbacks.append((callback_function, args))
	
	def call_callbacks(self, record):
		for callback in self.callbacks:
			func = callback[0]
			args = callback[1]
			args["record"] = record
			func(**args)
			args.pop("record") #delete record from args

"""
On stocke plein de LsrRecorder dans un dict de la classe LsrClient
1 recorder = 1 socket forcément
Objectif : pouvoir afficher plusieurs graphes simultanément sur une même fenêtre ...
Il va falloir threader ca en leur faisant partager la figure .. faisable mais comment on organise tout ca ...

On crée un client avec IP/PORT (réutilisés donc)
On teste la connexion avec connect_ex
On close le socket

Qd on demande à add_recorder()
On ouvre un socket avec le remote, qu'on authentifie et stocke dans un dict recorders (ajouté à la liste de recorders)
#si fail, on donne un msg d'erreur (mais on catch l'exception) pour ne pas quitter

lsr.close() => ferme tout
lsr.close("recorder_name")
lsr.finish() => close all
Du coup, on a tous les sockets en parallèles

Comment appliquer get_records dessus en threadé ...
Admettons qu'on ait tous les sockets
Recorder = socket + callback
lsr.bind("", func, name=test, yolo=data)
lsr.run()
lsr.finish()
"""

"""
Du coup, un usage multithreadé se ferait via les callbacks
avec lsr.CLien(host, ip)
lsr.add_recorder('name')
lsr.bind('name', function, kwargs)
lsr.add_recorder('name2')
lsr.bind('name2', function, kwargs)
lsr.run()
"""
