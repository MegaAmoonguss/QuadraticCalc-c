CC = gcc
CFLAGS = -Wall -std=c99 -O3
OUTFILE = qcc.out
SRCS = src/*.c src/*.h

all: $(SRCS)
	$(CC) $(CFLAGS) -o $(OUTFILE) $(SRCS) -lm

clean:
	$(RM) qcc.out