#!/bin/bash

../setup.sh
lib=""
for pparam in "$@"
do
    lib="$pparam $lib"
    echo "$lib"
done
gcc test.c $lib -o executable