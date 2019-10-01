#include "socket.h"

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
    char    buff[1024];

    sock = socket (AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        error("Socket failed");
    }


    server.sin_family = AF_INET;
    if (argc < 2) {
        error("Give me some");
    }
    hp = gethostbyname(argv[1]);
    if (hp == 0) {
        errornclose("gethostbyname failed", sock);
    }

    memcpy (&server.sin_addr, hp->h_addr, hp->h_length);
    server.sin_port = htons (PORT);

    if (connect (sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
        errornclose ("connect failed", sock);
    }

    printf("Send a message");
    while(1) {
        printf("Client: \t");
        scanf("%s", buff);
        send(sock, buff, strlen(buff), 0);
        if (strcmp(buff, "exit") == 0) {
            errornclose("Exiting the server " ,sock);
        }
        if ((recv(sock, buff, strlen(buff), 0)) < 0) {
            printf("Error recieving a message");
        } else {
            printf("Server: \t%s\n", buff);
        }
    }

    // printf ("%s\n", DATA);
    // close (sock);

    return 0;
}
