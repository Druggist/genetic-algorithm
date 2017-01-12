#!/bin/bash

for i in {0..9}
do
	mkdir -p "data/chart1/out/0$i"
	./bin/main.app "data/chart1/file_$i.txt" "data/chart1/out/0$i"/0"$i"_60.txt 1000000
done