#!/bin/bash

mkdir -p data
mkdir -p bin


g++ -g -Wall -std=c++11 src/generator.cpp src/instance.cpp src/maitenance.cpp src/task.cpp -o bin/generator.app
