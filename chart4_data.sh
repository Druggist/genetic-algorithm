#!/bin/bash

for ID in {50..950..50}
do
touch data/chart4/$ID/out/data.tx
	for f in data/chart4/$ID/out/*.txt
	do
		cat $f | head -n 2 | tail -n 1 >> data/chart4/$ID/out/data.tx
	done
	mv data/chart4/$ID/out/data.tx data/chart4/$ID/out/data.txt
done
