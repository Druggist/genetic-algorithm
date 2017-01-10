#!/bin/bash

for i in {0..9}
do
	./bin/main.app "data/tuning/file_$i.txt" "data/tuning/population_size/out_200_$i.txt" 1000
done