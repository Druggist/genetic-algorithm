#!/bin/bash

for i in {0..9}
do
	./bin/main.app "data/tuning/file_$i.txt" "data/tuning/mutation/out_50_$i.txt" 1000
done