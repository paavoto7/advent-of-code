#!/bin/bash

# Using a makefile would be a lot better, but this was just quickly done
# I might add a makefile later during the days especially when I have more helpers

# Makes it easier to run the programs. 
# Run using ./run.sh YEAR DAY_NUMBER [WHATEVER_TO_USE_TEST]
# Needs to have execute permission => chmod u+x run.sh

if [ "$2" = "clean" ]
then
    rm ./output/day*
    exit 0
fi

if [ -z "$1" ]
then
    echo "No year provided."
    exit 1
fi

if [ -z "$2" ]
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
    if [ "$2" -gt $day ]
    then
        echo "Day not yet available for this year"
        exit 1
    fi
fi

if [ ! -e "./$1/output/helper.o" ]
then
    g++ "./utils/helper.cpp" "./$1/day$2/day$2.cpp" -o "./$1/output/day$2"
else
    g++ "./$1/day$2/day$2.cpp" "./$1/$1/output/helper.o" -o "./$1/output/day$2"
fi

# Checks whether compilation was succesful or not
# $? means last commands return value, -ne is not equal
if [ $? -ne 0 ]
then
    echo "Compilation of the program failed."
    exit 1
fi

if [ -z "$3" ]
then
    ./$1/output/day$2 "./$1/inputs/day$2.txt"
else
    ./$1/output/day$2 "./$1/inputs/test.txt"
fi
