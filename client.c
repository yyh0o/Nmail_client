//
// Created by yyh on 18-7-30.
//

#include "client.h"



int clientRun(){
    int sockfd = new_connected_sock(SERV_IP, SERV_PORT);
    char sendBuff[FLAF_SIZE] = {0};
    char id[FLAF_SIZE] = {0};
    char pass[FLAF_SIZE] = {0};
//    while(1){
//        char *id;
//        char *pass;
//        signIn(sockfd, id, pass);
//        break;
//    }

    while (1) {
        scanf("%s", sendBuff);//输入发送数据
        fflush(stdin);//清除输入缓存
        int flag = 0;
        if ((flag = sendFlag(sockfd, sendBuff, id, pass)) == -1024)
            break;
        else{
            if (flag < 0){
                switch (flag){
                    case -1:
                        break;
                    case -2:
                        break;
                    case -3:
                        break;
                }
                continue;
            }
            switch (flag) {
                case RECV_MAIL:
                    ;
                    break;
                case CHECK_MAIL:
                    ;
                    break;
                case SEND_MAIL:
                    ;
                    break;
                case DEL_MAIL:
                    ;
                    break;
                case START_MAIL:
                    ;
                    break;
                case MODIFY_CONTACT:
                    ;
                    break;
                case MODIFY_BLACK_LIST:
                    ;
                    break;
                case STOP_LOOP:
                    break;
                case LOGIN:
                    printf("id:\n");
                    scanf("%s", id);
                    printf("pass:\n");
                    scanf("%s", pass);
                    signIn(sockfd, id, pass);
                default:
                    break;
            }
        }
    }
    close(sockfd);
    return 0;
}

int sendFlag(int socket, char* input, char* id, char* pass){
    int flag = 0;
    char type;
    mySendMsg(socket, id, FLAF_SIZE, MY_MSG);
    mySendMsg(socket, pass, FLAF_SIZE, MY_MSG);
    mySendMsg(socket, input, BUFFER_SIZE, MY_MSG);
    myRecvMsg(socket, &flag, &type);
    return flag;
}

int signIn(int sock, char* id, char* pass) {

    mySendMsg(sock, id, sizeof(id), MY_MSG);
    mySendMsg(sock, pass, sizeof(pass), MY_MSG);
    int flag = 0;
    char type;
    myRecvMsg(sock, &flag, &type);

    /*****测试****/
    printf("%d\n", flag);

    return flag;
}

int signUp(int sock, char* id, char* pass) {


    mySendMsg(sock, id, sizeof(id), MY_MSG);
    mySendMsg(sock, pass, sizeof(pass), MY_MSG);
    int flag = 0;
    char type;
    myRecvMsg(sock, &flag, &type);
    printf("%d\n", flag);
    return flag;
}