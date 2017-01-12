#!/bin/bash

for ID in {0..9}
do
touch data/chart0/out/0$ID/data1.tx
for f in data/chart0/out/0$ID/*.txt
do
	cat $f | head -n 2 | tail -n 1 | cut -c1-4 >> data/chart0/out/0$ID/data1.tx
done
	
	touch data/chart0/out/0$ID/data.txt
	cat data/chart0/out/0$ID/data1.tx | sort -Vr >> data/chart0/out/0$ID/data.txt

	rm -rf data/chart0/out/0$ID/data1.tx
done