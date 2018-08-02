//
//  packaging.h
//  22222
//
//  Created by 周彦錞 on 2018/8/1.
//  Copyright © 2018年 周彦錞. All rights reserved.
//

#ifndef packaging_h
#define packaging_h

#include <string.h>
typedef struct {
    char targetID[25]; //目标邮箱号
    char originID[25]; //发件人邮箱号
    char data[30];
    char title[50]; //邮件主题
    int state;// 0收藏,1已读，2未读
    int sendstate;//发送状态，成功为1，被拒收2
}MAILHEAD;
typedef struct {
    char content[500];//保存用户击键内容
    int appendixState;//有无附件，有则为1，无为0
    char appendixName[50];

}MAILBODY;
int separate(char* title);//文件拆封
int packaging(char* targetID,char* title,char* content,char* orid);//文件封装

#endif /* packaging_h */
