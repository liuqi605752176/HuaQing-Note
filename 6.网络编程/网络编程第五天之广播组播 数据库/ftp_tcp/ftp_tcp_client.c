//
// Created by liuqi on 4/11/18.
//


#include <mynet.h>
#include <apeu.h>
#include "my_ftp.h"


void user_list(int sockfd, my_ftp_data_t info);

void user_down(int sockfd, my_ftp_data_t info);

int main(int argc,char *argv[])
{
    int sockfd;

    sockfd = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in serveraddr;
    memset(&serveraddr,0,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = inet_addr("172.25.1.176");

    if(connect(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr)) == -1)
    {
        perror("connect");
        return -1;
    }
    my_ftp_data_t info;
    char buf[10];
    while(1)
    {
        printf("*************1.list*************\n");
        printf("*************2.down*************\n");
        printf("请输入想要进行的操作：");
        fgets(buf, sizeof(buf),stdin);
        info.choose = buf[0] - '0';

        switch(info.choose)
        {
            case 1:
                user_list(sockfd,info);
                break;
            case 2:
                user_down(sockfd,info);
                break;
        }

    }
    return 0;
}
void user_list(int sockfd, my_ftp_data_t info)
{
    int i;
    //发送标识符choose 给服务器
    info.choose = 1;
    send(sockfd,&info, sizeof(info),0);
    //接收服务器发送过来的文件名信息
    recv(sockfd,&info, sizeof(info),0);
    //打印文件名信息
    for(i = 0; i < strlen(info.data);i++)
    {
        printf("%c",info.data[i]);
    }
    printf("\n");

}
void user_down(int sockfd, my_ftp_data_t info)
{
    FILE *fp;
    printf("请输入需要下载的文件名：");
    //从终端输入需要下载的文件名
    fgets(info.fname, sizeof(info.fname),stdin);
    info.fname[strlen(info.fname) - 1] = '\0';

    //将需要下载的文件名发送给服务器端
    info.choose = 2;
    send(sockfd,&info,sizeof(info),0);

    //接收打开文件是否成功的标识符
    recv(sockfd,&info,sizeof(info),0);
    if(info.flag == FALSE)
    {
        printf("文件打开失败！\n");
        exit(EXIT_FAILURE);
    }
    if(info.flag == TRUE)
    {
        printf("文件打开成功！\n");
    }
    /************************开始接收数据**********************/
    //打开文件目录
    opendir("/home/liuqi/Documents/network/network_3/client");
    //改变文件目录，将需要下载的文件下载到指定目录
    chdir("/home/liuqi/Documents/network/network_3/client");
    //打开接收的文件信息
    fp = fopen(info.fname,"w");
    //循环接收文件数据
    while(1)
    {
        recv(sockfd,&info,sizeof(info),0);
        //将每次接收到的写进文件
        fwrite(info.data,1,info.len,fp);
        //判断写操作是不是最后一次
        if(info.len < sizeof(info.data))
            break;
    }
    printf("文件下载成功！\n");
    fclose(fp);
}

