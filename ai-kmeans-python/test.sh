#!/bin/sh
N=`wc -l < $1`
Nt=$((N-10))

rm -f ./results-*.txt

for ((nClust=1; nClust<Nt; nClust++))
do
    for ((i=0; i < 100; i++))
    do
        cat $1 | ./split.bash 10 ./kmeans.py $RANDOM $nClust
    done > results-$nClust.txt
done

