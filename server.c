#include "socket.h"

// void    error(char *msg) {
//     perror(msg);
//     exit(1);
// }

int     main(void) {

    int     sock;
    struct  sockaddr_in server;
    int     mysock;
    struct  sockaddr_in newAddr;
    char    buff[1024];
    socklen_t   addr_size;
    pid_t   childId;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        error("Failed to connect");
    }

    memset(&server, '\0', sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(5000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        error("Failed to bind");
    }
    listen (sock, 5);
     while (1) {
        mysock = accept (sock, (struct sockaddr *) &newAddr, &addr_size);
        if (mysock < 0)
            error("Accept failed");
        printf("Connected to %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

        if ((childId = fork()) == 0) {
            close(sock);
            while(1) {
                recv(mysock, buff, sizeof(buff), 0);
                if (strcmp(buff, "exit")) {
                    printf("Disconnecting from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
                    break ;
                } else {
                    printf ("Client: %s\n", buff);
                    send(sock, buff, strlen(buff), 0);
                    bzero(buff, sizeof(buff));
                }
            }
        }
        close (mysock);
    }

    return 0;
}
