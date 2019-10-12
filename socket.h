#ifndef SOCKET_H
#define SOCKET_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#define PORT 5000

typedef struct s_socket
{
    char*       hostname;
}               t_socket;

typedef struct s_server
{
    int         sock;
    int         mySock;
    char        buff[1024];
    pid_t       childId;
    struct sockaddr_in server;
    struct sockaddr_in newAddr;
    socklen_t   addr_size;
    
}               t_server;

typedef struct s_client
{
    int         sock;
    struct  sockaddr_in server;
    char        buff[1024];
}               t_client;


void    errornclose(char *msg, int sock);
void    error(char *msg);


#endif