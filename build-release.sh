#!/bin/bash

JOBS=$(nproc)

rm -f CMakeCache.txt
cmake -DCMAKE_BUILD_TYPE=Release -check-system-vars .
if [ $? -eq 0 ]; then
  make -j "$JOBS"
fi
