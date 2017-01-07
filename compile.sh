#!/bin/bash

mkdir -p data
mkdir -p bin

g++ -Wall -std=c++11 main.cpp machine.cpp maitenance.cpp order.cpp task.cpp generations.cpp  instance.cpp -o bin/main.app
g++ -Wall -std=c++11 generator.cpp maitenance.cpp task.cpp instance.cpp -o bin/generator.app
