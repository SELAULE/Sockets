#include "socket.h"


int     main(int argc, char **argv) {

    int     sock;
    struct  sockaddr_in server;
    int     mysock;
    struct  sockaddr_in newAddr;
    char    buff[1024];
    socklen_t   addr_size;
    pid_t   childId;

    if (argc != 2) {
        error("No port given");
        // exit(1);
    }
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        error("Failed to connect");
    }

    memset(&server, '\0', sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[1]));
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        error("Failed to bind");
    }
    listen (sock, 10);
     while (1) {
        mysock = accept(sock, (struct sockaddr *) &newAddr, &addr_size);
        if (mysock < 0)
            error("Accept failed");
        printf("Connected to %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

        if ((childId = fork()) == 0) {
            close(sock);
            while(1) {
                recv(mysock, buff, sizeof(buff), 0);
                if (strcmp(buff, "exit") == 0) {
                    printf("Disconnecting from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
                    break ;
                } else {
                    printf("Client: %s\n", buff);
                    if (send(mysock, buff, strlen(buff), 0) == -1) {
                        printf("Failed to send");
                    }
                    bzero(buff, sizeof(buff));
                }
            }
        }
        close (mysock);
    }

    return 0;
}
