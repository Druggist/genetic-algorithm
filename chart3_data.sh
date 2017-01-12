#!/bin/bash

for i in {0..9}
do
touch data/chart3/short_tasks/out/0$i/data.tx
	for f in data/chart3/short_tasks/out/0$i/*.txt
	do
		cat $f | head -n 2 | tail -n 1 >> data/chart3/short_tasks/out/0$i/data.tx
	done
	mv data/chart3/short_tasks/out/0$i/data.tx data/chart3/short_tasks/out/0$i/data.txt
done
