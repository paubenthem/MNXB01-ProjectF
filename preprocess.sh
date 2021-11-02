#!/bin/bash

mkdir data_clean

for file in $1/*
do
    CITYNAME=$(cat ${file} | sed '2q;d' | cut -d';' -f1)
    echo ${CITYNAME}
    cat ${file} | sed '0,/^Datum;Tid/d' | sed 's/;[GV].*//'| sed 's/[;:]/ /g' | sed 's/\([0-9]\)-/\1 /g' > data_clean/${CITYNAME}.csv
done
