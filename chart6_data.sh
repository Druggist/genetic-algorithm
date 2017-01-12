#!/bin/bash

for i in {5..50..5}
do
touch data/chart6/out/out_$i/data.tx
	for f in data/chart6/out/out_$i/*.txt
	do
		cat $f | head -n 2 | tail -n 1 >> data/chart6/out/out_$i/data.tx
	done
	mv data/chart6/out/out_$i/data.tx data/chart6/out/out_$i/data.txt
done
