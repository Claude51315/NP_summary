#include "common.h"
#define BUF_LEN 1024
int main(int argc, char *argv[]){

    if (argc < 3){
        printf("usage: %s <ip addr> <port>\n", argv[0]);
        return 0;
    }
    char *server_ip = argv[1];
    unsigned short server_port = atoi(argv[2]);
    char buf[BUF_LEN];
    int server_fd, count;
    server_fd = connect_server(server_ip, server_port);
    if(server_fd < 0){
        return 0;
    }
    memset(buf, '\0', BUF_LEN);
    count = read(server_fd, buf, sizeof(buf));
    printf("sever send : %s\n", buf);
    
    memset(buf, '\0', BUF_LEN);
    scanf("%s", buf);
    write(server_fd, buf, strlen(buf));
    memset(buf, '\0', BUF_LEN);
    count = read(server_fd, buf, sizeof(buf));
    printf("sever send : %s\n", buf);
    close(server_fd);





    return 0;
}
