#!/bin/sh

EXE=./gloves
RES=0

if $(test $($EXE < data/example1.txt) != 2); then
  echo "Example 1 does not work!"
  RES=1
fi

if $(test $($EXE < data/example2.txt) != -1); then
  echo "Example 2 does not work!"
  RES=1
fi

if $(test $($EXE < data/example3.txt) != 0); then
  echo "Example 3 does not work!"
  RES=1
fi

exit $RES
