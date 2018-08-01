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
#define SERV_PORT 2333
#define FLAF_SIZE 100
#define STOP_LOOP -1
#define RECV_MAIL 1
#define SEND_MAIL 2
#define CHECK_MAIL 3
#define DEL_MAIL 4
#define START_MAIL 5
#define MODIFY_CONTACT 6
#define MODIFY_BLACK_LIST 7
#define LOGIN 8
#define SINGUP 9
#define LOGOUT 10

int clientRun();
int sendFlag(int socket, int flag, char* id, char* pass);
int clientSignIn(int sock, char* id, char* pass);
int clientSignUp(int sock, char* id, char* pass);
int clientLogOut(int sock, char* id);

#endif //NMAIL_CLIENT_CLIENT_H
