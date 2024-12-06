#!/bin/bash

# Using a makefile would be a lot better, but this was just quickly done
# I might add a makefile later during the days especially when I have more helpers

# Makes it easier to run the programs. 
# Run using ./run.sh DAY_NUMBER [WHATEVER_TO_USE_TEST]
# Needs to have execute permission => chmod u+x run.sh

cd "$(dirname "$0")"

if [ -z "$1" ]
then
    echo "No day provided. Provide at least ./run.sh DAY_NUMBER."
    exit 1
fi

# Get the current day and month
printf -v day "%(%-d)T" -1
printf -v month "%(%-m)T" -1

# If it is december, check that the supplied day is not over the current one
if [ $month -eq 12 ]
then
    if [ "$1" -gt $day ]
    then
        echo "Day not yet available for this year"
        exit 1
    fi
fi

g++ "../2024/utils/helper.cpp" "./day$1/day$1.cpp" -o "./output/day$1.o"

# Checks whether compilation was succesful or not
# $? means last commands return value, -ne is not equal
if [ $? -ne 0 ]
then
    echo "Compilation of the program failed."
    exit 1
fi

if [ -z "$2" ]
then
    ./output/day$1.o "./inputs/day$1.txt"
else
    ./output/day$1.o "./inputs/test.txt"
fi
