#!/bin/bash

for i in {0..9}
do
	mkdir -p "data/chart3/long_tasks/out/0$i"
	./bin/main.app "data/chart3/long_tasks/file_$i.txt" "data/chart3/long_tasks/out/0$i"/0"$i"_60.txt 1000000
done