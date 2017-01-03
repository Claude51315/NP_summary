CC=gcc
CFLAG= -Wall -g
all: main

main: main.c
	${CC} ${CFLAG} main.c common.c -o $@
.phony: clean

clean:
	rm main
