#!/bin/sh

#  run.sh
#  HPC
#
#  Created by Sharan Thakur on 14/05/23.
#
echo "\nChoose program:\n"
for (( i = 1; i <= 5; i++ ))
    do
        echo "Prog$i.cpp"
done

echo ""

read -p "FileName? " fileName

clang++ -Xclang -fopenmp $LDFLAGS $CPPFLAGS  -lomp $fileName -o output && ./output
