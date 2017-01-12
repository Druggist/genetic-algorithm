#!/bin/bash

for ID in {100..1000..100}
do
touch data/chart5/$ID/out/data.tx
	for f in data/chart5/$ID/out/*.txt
	do
		cat $f | head -n 2 | tail -n 1 >> data/chart5/$ID/out/data.tx
	done
	mv data/chart5/$ID/out/data.tx data/chart5/$ID/out/data.txt
done
