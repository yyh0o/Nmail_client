//
// Created by yyh on 18-7-30.
//

#ifndef NMAIL_CLIENT_CLIENT_H
#define NMAIL_CLIENT_CLIENT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "mySocket.h"



#define SERV_IP "127.0.0.1"
#define SERV_PORT 23333
#define TMP_BUFFER_SIZE 100

int clientRun();

#endif //NMAIL_CLIENT_CLIENT_H
