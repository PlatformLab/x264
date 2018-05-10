#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: Install.sh <destination_prefix> <PerfUtils_location>"
    exit 1
fi

PREFIX=$1
PERFUTILS=$2

./configure --extra-ldflags="-L$PERFUTILS/lib -lPerfUtils -lstdc++" --extra-cflags="-I$PERFUTILS/include" --prefix=$PREFIX
make && make install
