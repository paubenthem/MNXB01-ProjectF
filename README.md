# MNXB01-ProjectF
This repo contains the code used to generate the graphs and pdf for our final project report.

## To use our code:

 * To use the code clone the repository.
 * Then run the preprocess.sh script passing in the foulder containing the raw data
 ```
 ./preprocess.sh datasets
 ```
 * Then start root in the `code` foulder.
 ```
 cd code
 root
 ```
 this will automatically compile all the code the first time it is used.
 * You can now use the methods we implipmented directly, or run the sample code
 in the `project.cpp` py calling `project()`.

## Contents:
 * The `code` foulder contains our root code that is based on the initial skeleton 
provided by the course MNXB01 given at lunds university.
 * The `datasets` and `raw data`  conatin the raw data which the course instructors
 have obtained from MSHI.
 * The `preprocess.sh` script is used to clean the raw data
 * The `workplan.txt` contains information about how we had decided to split up 
 the work initailly

