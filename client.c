#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

#define DATA "Package sent!!!"

void    error(char *msg) {
    perror(msg);
    exit(1);
}

void    errornclose(char *msg, int sock) {
    perror(msg);
    close(sock);
    exit(1);
}

int     main (int argc, char **argv) {
    int     sock;
    struct  sockaddr_in server;
    struct  hostent *hp;
    char buff[1024];

    sock = socket (AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        error("Socket failed");
    }


    server.sin_family = AF_INET;
    
    hp = gethostbyname(argv[1]);
    if (hp == 0) {
        errornclose("gethostbyname failed", sock);
    }

    memcpy (&server.sin_addr, hp->h_addr, hp->h_length);
    server.sin_port = htons (5000);

    if (connect (sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
        errornclose ("connect failed", sock);
    }

    if (send (sock, DATA, sizeof(DATA), 0) < 0) {
        errornclose("send failed", sock);
    }

    printf ("%s\n", DATA);
    close (sock);

    return 0;
}
