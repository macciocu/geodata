#!/bin/bash

WD=$(dirname $0)

SOURCES=$(find ./src -type f -iname *.cpp)
HEADERS=$(find ./src -type f -iname *.h)

echo $SOURCES
echo $HEADERS

for item in $SOURCES; do
  echo "clang-format -style=\"file\" -i \"$item\""
  clang-format -style="file" -i "$item"
done

for item in $HEADERS; do
  echo "clang-format -style=\"file\" -i \"$item\""
  clang-format -style="file" -i "$item"
done
