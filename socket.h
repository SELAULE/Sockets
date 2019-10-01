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

void    errornclose(char *msg, int sock);
void    error(char *msg);
#endif