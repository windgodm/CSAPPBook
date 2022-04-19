/* $begin hostinfo */
#include "csapp_netp_win.h"

int main(int argc, char **argv) 
{
    WSADATA wsaData;
    int nResult = -1;
    ADDRINFOA *p, *listp, hints;
    char buf[MAXLINE];
    int rc, flags;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <domain name>\n", argv[0]);
        exit(0);
    }

    nResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (nResult != 0) {
        printf("WSAStartup failed: %d\n", nResult);
        return 1;
    }

    /* Get a list of addrinfo records */
    memset(&hints, 0, sizeof(ADDRINFOA));                         
    hints.ai_family = AF_INET;       /* IPv4 only */        //line:netp:hostinfo:family
    hints.ai_socktype = SOCK_STREAM; /* Connections only */ //line:netp:hostinfo:socktype
    if ((rc = GetAddrInfo(argv[1], NULL, &hints, &listp)) != 0) {
        fprintf(stderr, "getaddrinfo error(%d): %s\n", rc, gai_strerror(rc));
        exit(1);
    }

    /* Walk the list and display each IP address */
    flags = NI_NUMERICHOST; /* Display address string instead of domain name */
    for (p = listp; p; p = p->ai_next) {
        GetNameInfo(p->ai_addr, p->ai_addrlen, buf, MAXLINE, NULL, 0, flags);
        printf("%s\n", buf);
    } 

    /* Clean up */
    FreeAddrInfo(listp);
    WSACleanup();

    exit(0);
}
/* $end hostinfo */
