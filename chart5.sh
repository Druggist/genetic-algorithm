#!/bin/bash

for i in {100..1000..100}
do
	mkdir -p data/chart5/$i
	./bin/generator.app 10 $i 100 0 "data/chart5/$i"
done