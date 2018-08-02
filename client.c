//
// Created by yyh on 18-7-30.
//

#include "client.h"
#include "packaging.h"
#include "contact.h"



int clientRun(){
    int sockfd = new_connected_sock(SERV_IP, SERV_PORT);
    char id[FLAF_SIZE] = {0};
    char pass[FLAF_SIZE] = {0};
    int tmp = 0;
    while (1) {
        displayMainMenu();
        int flag = 0;
        int mark = 0;
        scanf("%d", &flag);//输入发送数据
        if (flag == -1)
            break;
            switch (flag) {
                case RECV_MAIL:
                    clientRecvMail(sockfd, id, pass);
                    break;
                case CHECK_MAIL:
                    checkMail(sockfd, id, pass);
                    break;
                case SEND_MAIL:
                    sendMail(sockfd, id, pass);
                    break;
                case DEL_MAIL:
                    delMail(sockfd, id, pass);
                    break;
                case START_MAIL:
                    ;
                    break;
                case MODIFY_CONTACT:
                    editContect(sockfd, id, pass);
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
                    mark = clientSignIn(sockfd, id, pass);
                    switch (mark){
                        case 0:
                            printf("登陆成功\n");
                            break;
                        case -2:
                            printf("请先注册\n");
                            break;
                        case -3:
                            printf("密码错误\n");
                            break;
                        case -4:
                            printf("请勿重复登陆\n");
                            break;
                        default:
                            printf("未知错误\n");
                            break;
                    }
                    break;
                case SINGUP:
                    bzero(id, sizeof(id));
                    bzero(pass, sizeof(pass));
                    printf("id:\n");
                    scanf("%s", id);
                    printf("pass:\n");
                    scanf("%s", pass);
                    mark = clientSignUp(sockfd, id, pass);
                    switch (mark){
                        case 0:
                            printf("注册成功\n");
                            break;
                        case -3:
                            printf("该用户已存在\n");
                            bzero(id, sizeof(id));
                            bzero(pass, sizeof(pass));
                            break;
                        default:
                            printf("未知错误\n");
                            break;
                    }
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
    int flag;
    flag = LOGOUT;
    char buf[FLAF_SIZE] = {0};
    char type;
    strcat(buf, id);
    sendFlag(sock, flag, id, "");
    mySendMsg(sock, buf, sizeof(buf), MY_MSG);
    myRecvMsg(sock, buf, &type);
    return flag;
}

int clientSendMail(int sock, char* rid, char* title, char* content, char* id, char* pass) {
    int flag = SEND_MAIL;
    sendFlag(sock, flag, id, pass);
    packaging(rid, title, content, id);
    char fileName[50] = {0};
    char fileNames[50] = {0};
    strcat(fileName, "client/TemporaryStorage/");
    strcat(fileName, title);
    strcat(fileName, ".txt");
    strcat(fileNames, title);
    strcat(fileNames, ".txt");
    FILE* fp = fopen(fileName, "r");
    mySendFile(sock, fileNames, strlen(fileNames), fp);
    fclose(fp);
    char type;
    myRecvMsg(sock, &flag, &type);
    if (flag == 0){
        printf("发送成功\n");
    } else{
        printf("发送失败\n");
    }
    return flag;

}

void displayMainMenu(){
    printf("+==================Nmail======================+\n");
    printf("|              1: 接收邮件                      |\n");
    printf("|              2: 发送邮件                      |\n");
    printf("|              3: 查看邮件                      |\n");
    printf("|              4: 删除邮件                      |\n");
    printf("|              5: 收藏邮件                      |\n");
    printf("|              6: 编辑联系人                    |\n");
    printf("|              7: 编辑黑名单                    |\n");
    printf("|              8: 登陆                         |\n");
    printf("|              9: 注册                         |\n");
    printf("|              0: 注销                         |\n");
    printf("|             -1: 退出                         |\n");
    printf("+=============================================+\n");
}

void sendMail(int sock, char* myid, char* pass){
    char id[25] = {0};
    char title[50] = {0};
    char content[500] = {0};

    printf("输入邮件标题\n");
    scanf("%s", title);
    printf("输入收件人地址\n");
    scanf("%s", id);
    printf("请输入邮件内容,以'+'结束输入\n");
    char* tmp = content;
    char a;
    int count = 0;
    while ((a = getchar()) != '+'){
        *tmp = a;
        tmp++;
        count++;
        if (count >= 500){
            printf("输入已达到最大值\n");
            break;
        }
    }

    clientSendMail(sock, id, title, content, myid, pass);

}

void checkMail(int sock, char* id, char* pass) {
    printMailingLists();
    char title[FLAF_SIZE] = {0};
    int flag = 0;
    printf("输入邮件主题:\n");
    scanf("%s", title);
    flag = clientCheckMail(sock, id, pass, title);
    if (flag != CHECK_MAIL){
        printf("打开失败\n");
    }


}

int clientCheckMail(int sock, char* id, char* pass, char* title) {
    int flag = CHECK_MAIL;
    char type;
    char fileName[FILE_NAME_MAX_SIZE] = {0};
    flag =  sendFlag(sock, flag, id, pass);
    mySendMsg(sock, title, strlen(title)+1, MY_MSG);
    mySendMsg(sock, id, strlen(id)+1, MY_MSG);
    myRecvMsg(sock, &flag, &type);
    if (flag == CHECK_MAIL){
        myRecvFile(sock, "client/mainBox/", sizeof("client/mainBox/"), fileName);
        separate(title);
        return flag;
    }
    else {
        return flag;
    }
}

void delMail(int sock, char* id, char* pass) {
    char title[FLAF_SIZE] = {0};
    printMailingLists();
    printf("输入要删除的邮件主题:\n");
    scanf("%s", title);
    clientDelMail(sock, id, pass, title);

}

int clientDelMail(int sock, char* id, char* pass, char* title){
    char fileName[FILE_NAME_MAX_SIZE] = {0};
    int flag = DEL_MAIL;
    char type;
    sendFlag(sock, flag, id, pass);
    mySendMsg(sock, title, strlen(title) + 1, MY_MSG);
    mySendMsg(sock, id, strlen(id) + 1, MY_MSG);
    myRecvMsg(sock, &flag, &type);
    if (flag == DEL_MAIL){
        myRecvFile(sock, "client/mailBox/", sizeof("client/mailBox/"), fileName);
        bzero(fileName, sizeof(fileName));
        myRecvFile(sock, "client/mailBox/", sizeof("client/mailBox/"), fileName);
    }
    else {
        flag = -1;
    }
    return flag;
}


/*********************************************
客户端函数第一次运行时的初始化函数，负责建立用户邮箱
返回值：-2 创建目录失败
       0 成功
       -1 打开文件失败
**************************************************/
int clientInitiallization() {
    int state = 0;
    state = mkdir("client", 0777);//建立客户端根目录
    if (state < 0)
        return -2;
    int number=0;

    FILE *fp1;
    fp1 = fopen(BLACKLIST, "w+");//建立黑名单文件
    if (fp1==NULL)
        return -1;
    fclose(fp1);

    FILE *fp2;
    fp2 = fopen(BLACKLISTNUM, "w+");//建立黑名单人数文件
    if (fp2==NULL)
        return -1;
    fwrite(&number,sizeof(int),1,fp2);
    fclose(fp2);

    FILE *fp3;
    fp3 = fopen(PEIZHIWENJIAN, "w+");//建立用户个数文件
    if (fp3==NULL)
        return -1;
    fclose(fp3);

    FILE *fp4;
    fp4 = fopen(CONTACTLIST, "w+");//建立联系人文件
    if (fp4==NULL)
        return -1;
    fclose(fp4);

    FILE *fp5;
    fp5 = fopen(CONTACTLISTNUM, "w+");//建立联系人个数文件
    if (fp5==NULL)
        return -1;
    fwrite(&number,sizeof(int),1,fp5);
    fclose(fp5);
    state = mkdir("client/TemporaryStorage", 0777);
    if (state < 0)
        return -2;
    state = mkdir("client/mailBox", 0777);
    if (state < 0)
        return -2;
    FILE *fp6;
    fp6 = fopen("client/mailBox/list.txt", "w+");//建立邮箱列表
    if (fp6==NULL)
        return -1;
    fclose(fp6);

    FILE *fp7;
    fp7 = fopen("client/mailBox/mailNumber.txt", "w+");//建立邮箱个数文件
    if (fp7==NULL)
        return -1;
    fclose(fp7);
    return 0;
}

int editContect(int sock, char* id, char* pass) {
    displayContactList();
    char buf[50] = {0};
    printf("1: 添加联系人\n");
    printf("2: 删除联系人\n");
    int flag = 0;
    int mark = 0;
    scanf("%d", &flag);
    switch (flag) {
        case 1:
            printf("请输入添加的联系人id\n");
            scanf("%s", buf);
            mark = addContactList(buf);
            bzero(buf, sizeof(buf));
            switch (mark) {
                case 0:
                    printf("添加成功\n");
                    break;
                case -1:
                    printf("文件打开失败\n");
                    break;
                case -2:
                    printf("没有该联系人\n");
                    break;
                case -3:
                    printf("请勿重复添加\n");
                    break;
                default:
                    printf("未知错误\n");
                    break;
            }
            break;
        case 2:
            printf("请输入要删除的联系人id\n");
            scanf("%s", buf);
            mark = rmContactListByID(buf);
            if (mark){
                printf("未知错误\n");
            }
            else {
                printf("成功删除\n");
            }
            break;
        default:
            break;
    }

    flag = sendFlag(sock, MODIFY_CONTACT, id, pass);
    FILE* fp = fopen(CONTACT_LIST, 'r');
    if (!fp){
        printf("打开文件失败\n");
        return -1;
    }
    mySendMsg(sock, id, strlen(id) + 1, MY_MSG);
    mySendFile(sock, "contacts.txt", sizeof("contacts.txt"), fp);
    printf("同步成功\n");
    fclose(fp);
}

int clientRecvMail(int sock, char* id, char* pass) {
    int flag = RECV_MAIL;
    char type;
    char filename[FILE_NAME_MAX_SIZE] = {0};
    flag = sendFlag(sock, flag, id, pass);
    if (flag == RECV_MAIL){
        mySendMsg(sock, id, strlen(id)+1, MY_MSG);
        myRecvFile(sock, "client/mailBox/", sizeof("client/mailBox/"), filename);
        myRecvFile(sock, "client/mailBox/", sizeof("client/mailBox/"), filename);
        myRecvMsg(sock, &flag, &type);
        printMailingLists();
    }
    return flag;
}

int printMailingLists(void) {
    int number;
    FILE *fp1;
    fp1 = fopen("client/mailBox/mailNumber.txt", "r");
    if (fp1 == NULL) {
        return -1;
    }
    fread(&number, sizeof(int), 1, fp1);
    fclose(fp1);
    MAILHEAD head[100];
    FILE *fp;
    fp = fopen("client/mailBox/list.txt", "r");
    fread(head, sizeof(MAILHEAD), number, fp);
    fclose(fp);
    for (int i = 0; i < number; i++) {
        printf("Title: %s\n", head[i].title);
        printf("TargetID: %s\n", head[i].targetID);
        printf("OriginID: %s\n", head[i].originID);
        printf("Data: %s\n", head[i].data);
    }
    return 0;
}