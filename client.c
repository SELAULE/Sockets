#include "socket.h"

void    error(char *msg) {
    perror(msg);
    exit(1);
}

void    errornclose(char *msg, int sock) {
    perror(msg);
    close(sock);
    exit(1);
}

int     main (void) {
    int     sock;
    struct  sockaddr_in server;
    char    buff[1024];

    sock = socket (AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        error("Socket failed");
    }
    
    server.sin_family = AF_INET;

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

    return 0;
}
