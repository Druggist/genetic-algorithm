#!/bin/bash

mkdir -p "data/chart5/$1/out"
for i in {0..9}
do
	./bin/main.app "data/chart5/$1/file_"$i".txt" "data/chart5/$1/out/0"$i".txt" 1000
done