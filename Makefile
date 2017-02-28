CC=gcc
CFLAGS=-lm

build/QuadraticCalc-c: src/*
	$(CC) -o QuadraticCalc-c src/* $(CFLAGS)
