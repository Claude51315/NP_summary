CC=gcc
CFLAG= -Wall -g
all: server

server: server.c
	${CC} ${CFLAG} server.c common.c -o $@
.phony: clean

clean:
	rm server
