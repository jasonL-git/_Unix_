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
#if 0
    int sfd, cfd;
    struct sockaddr_un my_addr, peer_addr;
    socklen_t peer_addr_size;

    sfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sfd == -1)
        handle_error("socket");

    memset(&my_addr, 0, sizeof(struct sockaddr_un));
                        /* Clear structure */
    my_addr.sun_family = AF_UNIX;
    strncpy(my_addr.sun_path, MY_SOCK_PATH,
            sizeof(my_addr.sun_path) - 1);

    if (bind(sfd, (struct sockaddr *) &my_addr,
            sizeof(struct sockaddr_un)) == -1)
        handle_error("bind");

    if (listen(sfd, LISTEN_BACKLOG) == -1)
        handle_error("listen");

    /* Now we can accept incoming connections one
        at a time using accept(2) */

    peer_addr_size = sizeof(struct sockaddr_un);
    cfd = accept(sfd, (struct sockaddr *) &peer_addr,
                &peer_addr_size);
    if (cfd == -1)
        handle_error("accept");

    /* Code to deal with incoming connection(s)... */
    /* When no longer required, the socket pathname, MY_SOCK_PATH
        sould be deleted using unlink(2) or remove(3) */
#endif

    int       sock_fd, cfd = 0;
    int       ret, i = 0;
    socklen_t len = 0;
    char recv_buf[100] = {0};
    struct sockaddr_in seraddr, cliaddr = {0};
//stpe1: 创建socket套接字
    sock_fd = socket(AF_INET, SOCK_STREAM, 0); //用AF_INET就可，用AF_UNIX就一直bind失败
    if (sock_fd == -1)
        handle_error("socket");
    printf("socket success!\n");

    seraddr.sin_family = AF_INET;
    // seraddr.sin_addr.s_addr = inet_addr(SERVERADDR);
    seraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    seraddr.sin_port = htons(SERPORT);
    printf("ip addr: %ld, port: %d\n", seraddr.sin_addr.s_addr, seraddr.sin_port);

//step2: 将socket以及ip port绑定在一起
    if (bind(sock_fd, (struct sockaddr *)&seraddr, sizeof(seraddr)) == -1)
        handle_error("bind");
    printf("bind success\n");

//step3: 监听该端口
    if (listen(sock_fd, LISTEN_BACKLOG) == -1)
        handle_error("listen");
    printf("listen success\n");
//step4: 接受该端口,并且返回与其相连的socket另一端
    len = sizeof(cliaddr);
    cfd = accept(sock_fd, (struct sockaddr *)&cliaddr, &len);
    if (cfd == -1)
        handle_error("accept");
    printf("accept success!\n");
//step5： 接收另外一端发来的数据
    ret = recv(cfd, recv_buf, sizeof(recv_buf), 0);
    if (ret == -1)
        handle_error("recv");
    printf("recv success, the recv number is : \n");
    for (i = 0; i< sizeof(recv_buf); i++)
    {
        printf("recv_buf[%d] : %d \n", i, recv_buf[i]);
    }
    
}