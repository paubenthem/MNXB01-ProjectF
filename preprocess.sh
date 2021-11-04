#!/bin/bash
if  [[ $# -eq 1 && -d "$1" ]] ; then #check that arg is foulder
    mkdir -p data_clean 
    for file in $1/*.csv
    do
        CITYNAME=$(cat ${file} | sed '2q;d' | cut -d';' -f1)
        echo ${CITYNAME}
        cat ${file} | #load in file
            sed '0,/^Datum;Tid/d' | #remove header and lines before
            sed 's/;[GVY].*//' | #remove the quality code and anything after 
            sed 's/[;:]/ /g' | #Change ; and : to ' ' (space) 
            sed 's/\([0-9]\)-/\1 /g' > "data_clean/${CITYNAME}.csv" #remove the - in date and save to new file
    done
else
    echo "The first argument needs to be a directory containing the raw data as .csv files"
fi
