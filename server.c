#include "socket.h"


int     main(int argc, char **argv) {
    t_socket t_socket;
    t_server server;

    if (argc != 2) {
        error("No port given");
        // exit(1);
    }
    printf("are at least here!!!!!!");
    printf("Buddy\t%s\n", t_socket.hostname);

    server.sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server.sock < 0) {
        error("Failed to connect");
    }
    printf("%s", argv[1]);

    memset(&server.server, '\0', sizeof(server.server));
    server.server.sin_family = AF_INET;
    server.server.sin_port = htons(PORT);
    server.server.sin_addr.s_addr = inet_addr("127.0.0.1");


    if (bind(server.sock, (struct sockaddr *)&server.server, sizeof(server.server)) < 0) {
        error("Failed to bind");
    }
    listen (server.sock, 10);
     while (1) {
        server.mySock = accept(server.sock, (struct sockaddr *) &server.newAddr, &server.addr_size);
        if (server.mySock < 0)
            error("Accept failed");
        printf("Connected to %s:%d\n", inet_ntoa(server.server.sin_addr), ntohs(server.server.sin_port));
        if ((server.childId = fork()) == 0) {
            close(server.sock);
            while(1) {
                recv(server.mySock, server.buff, sizeof(server.buff), 0);
                if (strcmp(server.buff, "exit") == 0) {
                    printf("Disconnecting from %s:%d\n", inet_ntoa(server.server.sin_addr), ntohs(server.server.sin_port));
                    break ;
                } else {
                    printf("Client: %s\n", server.buff);
                    if (send(server.mySock, server.buff, strlen(server.buff), 0) == -1) {
                        printf("Failed to send");
                    }
                    bzero(server.buff, sizeof(server.buff));
                }
            }
        }
        close (server.mySock);
    }
    return 0;
}
