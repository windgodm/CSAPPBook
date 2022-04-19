/* 
 * echoserveri.c - An iterative echo server 
 */ 
/* $begin echoserverimain */
#include "csapp_netp_win.h"

void echo(int connfd);

int main(int argc, char **argv) 
{
    WSADATA wsaData;
    int nResult = -1;
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;  /* Enough space for any address */  //line:netp:echoserveri:sockaddrstorage
    char client_hostname[MAXLINE], client_port[MAXLINE];

    if (argc != 2) {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    nResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (nResult != 0) {
        printf("WSAStartup failed: %d\n", nResult);
        return 1;
    }

    listenfd = Open_listenfd(argv[1]);
    while (1) {
	clientlen = sizeof(struct sockaddr_storage); 
	connfd = accept(listenfd, (SOCKADDR *)&clientaddr, &clientlen);
        GetNameInfo((SOCKADDR *)&clientaddr, clientlen, client_hostname, MAXLINE, 
                    client_port, MAXLINE, 0);
        printf("Connected to (%s, %s)\n", client_hostname, client_port);
        echo(connfd);
        closesocket(connfd);
    }
    WSACleanup();
    exit(0);
}
/* $end echoserverimain */
