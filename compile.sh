#!/bin/bash

mkdir -p data
mkdir -p bin

g++ -g -Wall -std=c++11 src/main.cpp src/machine.cpp src/maitenance.cpp src/order.cpp src/task.cpp src/generations.cpp src/instance.cpp -o bin/main.app

g++ -g -Wall -std=c++11 src/generator.cpp src/instance.cpp src/maitenance.cpp src/task.cpp -o bin/generator.app
