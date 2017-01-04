CC=gcc
CFLAG= -Wall -g
all: server client

server: server.c
	${CC} ${CFLAG} server.c common.c -o $@
client: client.c
	${CC} ${CFLAG} client.c common.c -o $@



.phony: clean

clean:
	rm server client
