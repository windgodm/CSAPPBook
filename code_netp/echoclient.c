/*
 * echoclient.c - An echo client
 */
/* $begin echoclientmain */
#include "csapp_netp_win.h"

int main(int argc, char **argv) 
{
    WSADATA wsaData;
    int nResult = -1;
    int clientfd;
    char *host, *port, buf[MAXLINE];
    rio_t rio;

    if (argc != 3) {
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
        exit(0);
    }

    nResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (nResult != 0) {
        printf("WSAStartup failed: %d\n", nResult);
        return 1;
    }

    host = argv[1];
    port = argv[2];

    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);

    while (fgets(buf, MAXLINE, stdin) != NULL) {
        Rio_writen(clientfd, buf, strlen(buf));
        Rio_readlineb(&rio, buf, MAXLINE);
        fputs(buf, stdout);
    }
    closesocket(clientfd); //line:netp:echoclient:close
    WSACleanup();
    exit(0);
}
/* $end echoclientmain */
