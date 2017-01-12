#!/bin/bash

for i in {0..9}
do
	mkdir -p "data/chart0/out/0$i"
	./bin/main.app "data/chart0/file_$i.txt" "data/chart0/out/0$i"/0"$i.txt" 15000
done