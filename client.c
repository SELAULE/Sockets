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

int     main (int argc, char** argv) {

    t_client client;
    t_socket t_socket;
    t_socket.hostname = argv[1];

    if (argc != 2) {
        error("No port given");
    }
    client.sock = socket (AF_INET, SOCK_STREAM, 0);
    if (client.sock < 0) {
        error("Socket failed");
    }

    client.server.sin_family = AF_INET;
    client.server.sin_port = htons (atoi(argv[1]));
    client.server.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect (client.sock, (struct sockaddr *) &client.server, sizeof(client.server)) < 0) {
        printf("%d\n", connect (client.sock, (struct sockaddr *) &client.server, sizeof(client.server)));
        errornclose ("connect failed", client.sock);
    }

    printf("Send a message\n");
    while(1) {
        printf("Client: \t");
        scanf("%s", client.buff);
        send(client.sock, client.buff, strlen(client.buff), 0);
        if (strcmp(client.buff, "exit") == 0) {
            errornclose("Exiting the server ", client.sock);
        }
        if ((recv(client.sock, client.buff, strlen(client.buff), 0)) < 0) {
            printf("Error recieving a message");
        } else {
            printf("Server: \t%s\n", client.buff);
        }
    }

    return 0;
}
