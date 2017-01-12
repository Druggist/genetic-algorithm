#!/bin/bash

mkdir -p "data/chart4/$1/out"
for i in {0..19}
do
	if [ $i -lt 10 ]; then
	./bin/main.app "data/chart4/$1/file_"$i".txt" "data/chart4/$1/out/0"$i".txt" 100000
	else
	./bin/main.app "data/chart4/$1/file_"$i".txt" "data/chart4/$1/out/"$i".txt" 100000
	fi
done