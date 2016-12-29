#!/bin/bash

mkdir -p data
mkdir -p bin

g++ -Wall -std=c++11 src/generator.cpp -o bin/generator.app
g++ -Wall -std=c++11 src/main.cpp src/machine.cpp src/maitenance.cpp src/order.cpp src/task.cpp  -o bin/main.app