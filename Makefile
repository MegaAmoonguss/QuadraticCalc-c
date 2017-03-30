CC = gcc
CFLAGS = -Wall -std=c99 -lm -O3
OUTFILE = QuadraticCalc-c
SRCS = src/*.c src/*.h

$(OUTFILE): $(SRCS)
	$(CC) $(CFLAGS) -o $(OUTFILE) $(SRCS)
