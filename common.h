#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctype.h>
#include <strings.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/select.h>
#include <fcntl.h>
#include <errno.h>

#define LISTEN_NUM 30

/* read one line of data from fd*/
int get_line(int fd, char* buf, int buf_len, int flag);
int set_nonblock(int fd);
/* return server fd if the specified port can be listened*/
int create_server(unsigned short port);
int get_client_connection(int server_fd);
#endif
