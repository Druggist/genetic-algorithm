#!/bin/bash

for i in {0..9}
do
	touch data/chart1/out/0$i/data.tx
	for f in data/chart1/out/0$i/*.txt
	do
		cat $f | head -n 2 | tail -n 1 | cut -c1-4 >> data/chart1/out/0$i/data.tx
	done
	mv data/chart1/out/0$i/data.tx data/chart1/out/0$i/data.txt
done
