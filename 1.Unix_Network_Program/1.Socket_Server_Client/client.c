#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>

#define MY_SOCK_PATH "/somepath"
#define LISTEN_BACKLOG 50

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)    

#define SERVERADDR      "192.168.123.100"
#define SERPORT         6600
int
main(int argc, char *argv[])
{
    int       sock_fd, cfd = 0;
    int       ret, i = 0;
    socklen_t len = 0;
    char send_buf[100] = {0};
    struct sockaddr_in seraddr, cliaddr = {0};

    sock_fd = socket(AF_INET, SOCK_STREAM, 0); //用AF_INET就可，用AF_UNIX就一直bind失败
    if (sock_fd == -1)
        handle_error("socket");
    printf("socket success!\n");

    seraddr.sin_family = AF_INET;
    // seraddr.sin_addr.s_addr = inet_addr(SERVERADDR);
    seraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    seraddr.sin_port = htons(SERPORT);
    printf("ip addr: %ld, port: %d\n", seraddr.sin_addr.s_addr, seraddr.sin_port);
    // if (bind(sock_fd, (struct sockaddr *)&seraddr, sizeof(seraddr)) == -1)
    //     handle_error("bind");
    // printf("bind success\n");

    // if (listen(sock_fd, LISTEN_BACKLOG) == -1)
    //     handle_error("listen");
    // printf("listen success\n");

    // cfd = accept(sock_fd, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
    // if (cfd == -1)
    //     handle_error("accept");
    // printf("accept success!\n");

    // ret = recv(cfd, recv_buf, sizeof(recv_buf), 0);
    // if (ret == -1)
    //     handle_error("recv");
    // printf("recv success, the recv number is : \n");
    // for (i = 0; i< sizeof(recv_buf); i++)
    // {
    //     printf("recv_buf[%d] : %d, ", i, recv_buf[i]);
    // }
    
    if (connect(sock_fd, (struct sockaddr *)&seraddr, sizeof(seraddr)) == -1)
        handle_error("connect");
    printf("connect success\n");

    for (i = 0; i< sizeof(send_buf); i++)
    {
        send_buf[i] = i;
    }

    ret = send(sock_fd, send_buf, sizeof(send_buf), 0);
    if (ret == -1)
        handle_error("send");
    printf("send success\n");

}