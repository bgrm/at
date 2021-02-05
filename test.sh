#!/bin/sh

make
./heap < $1 > heap.out
./tree < $1 > tree.out
./array < $1 > array.out

diff heap.out array.out	
if [ $? -ne 0 ]; then
	echo 'Heap and array give DIFFERENT answers!';
fi

diff heap.out tree.out	
if [ $? -ne 0 ]; then
	echo 'Heap and tree give DIFFERENT answers!';
fi



