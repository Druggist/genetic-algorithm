#!/bin/bash

for i in {50..950..50}
do
touch data/chart2/out/out_$i/data.tx
	for f in data/chart2/out/out_$i/*.txt
	do
		cat $f | head -n 2 | tail -n 1 >> data/chart2/out/out_$i/data.tx
	done
	mv data/chart2/out/out_$i/data.tx data/chart2/out/out_$i/data.txt
done
