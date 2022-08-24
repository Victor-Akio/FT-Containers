#!/bin/bash

if [ $1 = v ]; then
	./containers-std -V > vector-std-test.txt
	./containers-ft -V > vector-ft-test.txt

	diff -y vector-std-test.txt vector-ft-test.txt

elif [ $1 = m ]; then
	./containers-std -M > map-std-test.txt
	./containers-ft -M > map-ft-test.txt

	diff -y map-std-test.txt map-ft-test.txt

elif [ $1 = s ]; then
	./containers-std -S > stack-std-test.txt
	./containers-ft -S > stack-ft-test.txt

	diff -y stack-std-test.txt stack-ft-test.txt

else
	echo "Please, try to use [bash test.sh <flag>], after running make."
	echo "where \"v\" is vector, \"m\" is map and \"s\" is stack."
	echo "ex: bash test.sh v"
fi
