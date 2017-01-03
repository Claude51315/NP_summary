#include "common.h"
int get_line(int fd, char* buf, int buf_len, int flag)
{
    int base = 0 ; 
    char tmp = '\0';
    int n ;
    set_nonblock(fd);
    while( base < buf_len && tmp != '\n' ){
        n = recv(fd, &tmp, 1 , flag);
        if(n > 0){
            /* http line should end with /r/n */
            if(tmp == '\r'){
                /* using MSG_PEEK won't clear the internal buffer data*/
                n = recv(fd, &tmp, 1, MSG_PEEK);
                if(n > 0 && tmp == '\n'){
                    n = recv(fd, &tmp, 1, flag);
                } else{
                    tmp = '\n';
                }
            }
            buf[base] = tmp;
            base ++;
        } else {
            if(errno != EAGAIN)
                printf("error : %s <br /> \n", strerror(errno));
            return n ;
        } 
    }
    buf[base] = '\0';
    return base;
}
int set_nonblock(int fd)
{
    int flag;
    flag = fcntl(fd, F_GETFL, 0);
    flag |= O_NONBLOCK;
    fcntl(fd, F_SETFD, flag);
    return 0;
}
int create_server(unsigned short port){
    int server_fd;
    int ret ;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_info;
    memset(&server_info, 0, sizeof(server_info));
    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(port);
    server_info.sin_addr.s_addr = htonl(INADDR_ANY);
    ret = bind(server_fd, (struct sockaddr*)&server_info, sizeof(server_info));
    if(ret < 0){
        fprintf(stderr, "bind port %u error\n", port);
        return -1;
    }
    ret = listen(server_fd, LISTEN_NUM);
    if(ret < 0){
        fprintf(stderr, "listen port %u error\n", port);
        return -1;
    }
    return server_fd;
}
int get_client_connection(int server_fd){
    int client_fd;
    socklen_t client_len;
    struct sockaddr_in client_addr;
    client_len = sizeof(client_addr);
    memset(&client_addr, 0, client_len);
    client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
    if( client_fd < 0 ){
        fprintf(stderr, "accept error\n");
        return -1;
    }
    return client_fd;
}