#!/bin/bash

if [ ! -d build ]
then
	mkdir build
fi
gcc -o build/QuadraticCalc-c src/* -lm
