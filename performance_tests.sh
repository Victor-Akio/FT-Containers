#!/bin/bash

if [ $1 = v ]; then
	echo "Vector STD performance "
	sleep 0.000001 && time ./containers-std -V > /dev/null
	echo "Vector FT performance"
	time ./containers-ft -V > /dev/null

elif [ $1 = m ]; then
	echo "Map STD performance"
	sleep 0.000001 && time ./containers-std -M > /dev/null
	echo "Map FT performance"
	time ./containers-ft -M > /dev/null

elif [ $1 = s ]; then
	echo "Stack STD performance"
	sleep 0.000001 && time ./containers-std -S > /dev/null
	echo "Stack FT performance"
	time ./containers-ft -S > /dev/null

else
	echo "Please, try to use [bash performance_tests.sh <flag>], after running make."
	echo "where \"v\" is vector, \"m\" is map and \"s\" is stack."
	echo "ex: bash performance_tests.sh v"
fi