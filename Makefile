CC=gcc
CFLAGS=-lm

build/QuadraticCalc-c: src/*
	$(CC) -o QuadraticCalc-c src/* $(CFLAGS)

CC = gcc
CFLAGS = -Wall -std=c99 -lm
OUTFILE = QuadraticCalc-c
SRCS = src/*.c src/*.h

$(OUTFILE): $(SRCS)
        $(CC) $(CFLAGS) -o $(OUTFILE) $(SRCS)