//
// Created by yyh on 18-7-30.
//

#include "client.h"



int clientRun(){
    int sockfd = new_connected_sock(SERV_IP, SERV_PORT);
    char sendBuff[FLAF_SIZE] = {0};
    char id[FLAF_SIZE] = {0};
    char pass[FLAF_SIZE] = {0};
    int tmp = 0;
//    while(1){
//        char *id;
//        char *pass;
//        signIn(sockfd, id, pass);
//        break;
//    }

    clientSignIn(sockfd, "123", "123");

    while (1) {
        int flag = 0;
        scanf("%d", &flag);//输入发送数据
        if (flag == -1024)
            break;
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
                    clientSignIn(sockfd, id, pass);
                    break;
                case SINGUP:
                    bzero(id, sizeof(id));
                    bzero(pass, sizeof(pass));
                    printf("id:\n");
                    scanf("%s", id);
                    printf("pass:\n");
                    scanf("%s", pass);
                    clientSignUp(sockfd, id, pass);
                    break;
                case LOGOUT:
                    clientLogOut(sockfd, id);
                    break;
                default:
                    break;
            }
        }
    close(sockfd);
    return 0;
}

int sendFlag(int socket, int flag, char* id, char* pass){
    char type;
    char buf[FLAF_SIZE] = {0};
    mySendMsg(socket, &flag, sizeof(flag), MY_MSG);
    strcat(buf, id);
    mySendMsg(socket, buf, sizeof(buf), MY_MSG);
    bzero(buf, sizeof(buf));
    strcat(buf, pass);
    mySendMsg(socket, buf, sizeof(buf), MY_MSG);
    myRecvMsg(socket, &flag, &type);
    return flag;
}

int clientSignIn(int sock, char* id, char* pass) {
    int flag = LOGIN;
    char type;

    sendFlag(sock, flag, id, pass);

    mySendMsg(sock, id, sizeof(id), MY_MSG);
    mySendMsg(sock, pass, sizeof(pass), MY_MSG);

    myRecvMsg(sock, &flag, &type);

    /*****测试****/
//    printf("%d\n", flag);

    return flag;
}

int clientSignUp(int sock, char* id, char* pass) {
    int flag = SINGUP;
    char type;
    sendFlag(sock, flag, id, pass);
    mySendMsg(sock, id, sizeof(id), MY_MSG);
    mySendMsg(sock, pass, sizeof(pass), MY_MSG);
    myRecvMsg(sock, &flag, &type);
    printf("%d\n", flag);
    return flag;
}

int clientLogOut(int sock, char* id){
    if (strcmp(id, "") == 0){
        printf("no login\n");
        return -1;
    }
    char buf[FLAF_SIZE] = {0};
    strcpy(buf, id);
    char type;
    mySendMsg(sock, buf, sizeof(buf), MY_MSG);
    bzero(buf, sizeof(buf));
    myRecvMsg(sock, buf, &type);
    printf("logout");
    return 0;
}