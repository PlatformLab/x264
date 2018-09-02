#!/bin/bash

if [ "$#" -ne 3 ]; then
    echo "Usage: Install.sh <destination_prefix> <PerfUtils_location> <nice:0/1>"
    exit 1
fi

PREFIX=$1
PERFUTILS=$2
USE_NICE=$3
NICE_FLAG="-DNICE"

if [[ $USE_NICE == 0 ]]; then
    NICE_FLAG="-DNNICE"
fi

# Use NICE flag to decide whether to set the nice value for x264.
./configure --extra-ldflags="-L$PERFUTILS/lib -lPerfUtils -lstdc++" --extra-cflags="-I$PERFUTILS/include $NICE_FLAG" --prefix=$PREFIX
make && make install
