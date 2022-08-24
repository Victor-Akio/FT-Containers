#!/bin/bash

if [ $1 = v ]; then
	echo "Vector STD performance "
	time ./containers-std -V > /dev/null
	echo ""
	echo "Vector FT performance"
	time ./containers-ft -V > /dev/null
	echo ""

elif [ $1 = m ]; then
	echo "Map STD performance"
	time ./containers-std -M
	echo ""
	echo "Map FT performance"
	time ./containers-ft -M
	echo ""

elif [ $1 = s ]; then
	echo "Stack STD performance"
	time ./containers-std -S > /dev/null
	echo ""
	echo "Stack FT performance"
	time ./containers-ft -S > /dev/null
	echo ""

else
	echo "Please, try to use [bash performance_tests.sh <flag>], after running make."
	echo "where \"v\" is vector, \"m\" is map and \"s\" is stack."
	echo "ex: bash performance_tests.sh v"
	echo ""
fi