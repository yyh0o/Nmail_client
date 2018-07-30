//
// Created by yyh on 18-7-30.
//

#include "client.h"



int clientRun(){
    int sockfd = new_connected_sock(SERV_IP, SERV_PORT);
    char sendBuff[BUFFER_SIZE];
    char rcevBuff[BUFFER_SIZE];
    bzero(sendBuff,BUFFER_SIZE);
    bzero(rcevBuff,BUFFER_SIZE);
    
    while (1) {
        scanf("%s", sendBuff);//输入发送数据
        fflush(stdin);//清除输入缓存

        if (strcmp(sendBuff, "exit") == 0) {
            mySendMsg(sockfd, "0", 0, 'x');
            break;
        }
        if (mySendMsg(sockfd, sendBuff, sizeof(sendBuff), '1') == -1) {
            perror("send");
            exit(EXIT_FAILURE);
        }
        char* type;
        myRecvMsg(sockfd, rcevBuff, &type);
        printf("%s", rcevBuff);
    }
    close(sockfd);
    exit(0);
}
