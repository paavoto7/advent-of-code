#!/bin/bash

# Makes it easier to test the program. Run using ./run.sh
# Needs to have execute permission => chmod u+x run.sh

cd $(dirname $0)

g++ ./2024/utils/helper.cpp ./2024/day$1/day$1.cpp -o ./output/day$1.o
./output/day$1.o ./inputs/day$1.txt $2