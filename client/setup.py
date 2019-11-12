#!/usr/bin/python3
from setuptools import setup, find_packages
import Lsr

setup(
    name='Lsr',
    version=Lsr.__version__,
    packages=find_packages(),
    author="0xukn",
    author_email="0xUKN@protonmail.com",
    description="Client for the Lsr library",
    long_description=open('README.md').read(),
    url='https://github.com/PoussPouss/lightweight_simulator_robot',
    license="WTFPL" 
)
