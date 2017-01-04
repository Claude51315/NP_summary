#include "common.h"
#define BUF_LENGTH (1024)
int main(int argc, char* argv[])
{
    if(argc < 2 ){
        printf("usage : ./%s <port>\n", argv[0] );
        return 0;
    }
    int port = atoi(argv[1]);
    int server_fd, max_fd_num;
    int ret;
    char msg_buf[BUF_LENGTH];
    fd_set master, wr_set, rd_set;
    server_fd = create_server(port);
    if(server_fd < 0){
        return 0;
    }
    max_fd_num = server_fd;
    FD_ZERO(&master);
    FD_ZERO(&wr_set);
    FD_ZERO(&rd_set);
    FD_SET(server_fd, &master);
    for(;;)
    {
        memcpy(&wr_set, &master, sizeof(fd_set));
        memcpy(&rd_set, &master, sizeof(fd_set));
        ret = select(max_fd_num + 1, &rd_set, &wr_set, NULL, NULL);
        if(ret < 0){
            fprintf(stderr, "select error\n");
            return 0;
        }
        for(int i = 0 ; i < max_fd_num + 1; i++ )
        {
            if(FD_ISSET(i, &rd_set)){
                if(i == server_fd){ // new connection
                    int client_fd = get_client_connection(server_fd);
                    if(client_fd > 0 ){
                        FD_SET(client_fd, &master);
                        max_fd_num = (client_fd > max_fd_num) ? client_fd : max_fd_num;
                    }
                    memset(msg_buf, '\0', BUF_LENGTH);
                    sprintf(msg_buf, "welcome!\n");
                    write(client_fd, msg_buf, strlen(msg_buf));
                } else { // read msg from client
                    memset(msg_buf, '\0', BUF_LENGTH);
                    int count = read(i, msg_buf, BUF_LENGTH);
                    write(i, msg_buf, count); 
                }
            }
        }
    
    }
    return 0;
}
