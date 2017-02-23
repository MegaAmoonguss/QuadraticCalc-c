CC=gcc
CFLAGS=-lm

build/QuadraticCalc-c: src/*
	$(CC) -o build/QuadraticCalc-c src/* $(CFLAGS)
