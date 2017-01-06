#!/bin/bash

mkdir -p data
mkdir -p bin

g++ -Wall -std=c++11 main.cpp machine.cpp maitenance.cpp order.cpp task.cpp generations.cpp  -o main.app
