#!/bin/bash

for i in {50..950..50}
do
	mkdir -p data/chart2/$i
	./bin/generator.app 10 100 $i 0 "data/chart2/$i"
done