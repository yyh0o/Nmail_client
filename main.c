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

//int main(int argc, char *argv[]) {
//    int socketfd;//套接字
//    unsigned short port = 23333;
//    struct sockaddr_in address;
//    if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
//        perror("socket");
//        exit(EXIT_FAILURE);
//    }
////    memset(&address,0, sizeof(address));
//    bzero(&address, sizeof(address));
//    address.sin_family = AF_INET;
//    address.sin_port = htons(port);
//    inet_pton(AF_INET, SERV_IP, &address.sin_addr);
//
//
//    if (connect(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
//        perror("connect");
//        exit(EXIT_FAILURE);
//    }
//    char char_send[100]; //发送数据缓冲区
//    char char_rcev[100]; //接收数据缓冲区
//
//    myRecvFile(socketfd,"../",4);
//
//    for (;;) {
//        scanf("%s", char_send);//输入发送数据
//        fflush(stdin);//清除输入缓存
////        if(strcmp(char_send, "exit")==0){//如果输入exit，跳出循环
////            if((send(socketfd,char_send,100,0))==-1)
////            {
////                perror("send");
////                exit(EXIT_FAILURE);
////            }
////            break;
////        }
////        if((send(socketfd,char_send,100,0))==-1)
////        {
////            perror("send");
////            exit(EXIT_FAILURE);
////        }
////        recv(socketfd,char_rcev,100,0);
////        printf("%s",char_rcev);
//
//        if (strcmp(char_send, "exit") == 0) {
//            mySendMsg(socketfd, "0", 0, 'x');
//            break;
//        }
//        if (mySendMsg(socketfd, char_send, sizeof(char_send), '1') == -1) {
//            perror("send");
//            exit(EXIT_FAILURE);
//        }
//        char* type;
//        myRecvMsg(socketfd, char_rcev, &type);
//        printf("%s", char_rcev);
//    }
//    close(socketfd);
//    exit(0);
//
//}

int main(int argc, char *argv[]) {
    clientRun();
}