#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "mySocket.h"
#include "client.h"

#define SERV_IP "127.0.0.1"

int main(int argc, char *argv[]) {
    clientRun();
    return 0;
}