#!/bin/bash

JOBS=$(nproc)

rm -f CMakeCache.txt
cmake -DCMAKE_BUILD_TYPE=Debug -check-system-vars .
if [ $? -eq 0 ]; then
  make -j "$JOBS"
fi

rm -f CMakeCache.txt
cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_UNITTEST=ON -check-system-vars .
if [ $? -eq 0 ]; then
  make -j "$JOBS"
fi

rm -f CMakeCache.txt
cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_E2E=ON -check-system-vars .
if [ $? -eq 0 ]; then
  make -j "$JOBS"
fi
