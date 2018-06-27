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
    int sockfd,condfd;

    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd == -1)
    {
        perror("socket");
        return -1;
    }

    struct sockaddr_in serveraddr,clientaddr;

    memset(&serveraddr,0, sizeof(serveraddr));
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr("172.25.1.176");

    if(bind(sockfd,(const struct sockaddr *)&serveraddr, sizeof(serveraddr)) == -1)
    {
        perror("bind");
        return -1;
    }
    if(listen(sockfd,5) == -1)
    {
        perror("listen");
        return -1;
    }

    socklen_t len = sizeof(clientaddr);

    pid_t pid;

    ssize_t reval;

    signal(SIGCHLD,SIG_IGN);
    my_ftp_data_t info;
    while(1)
    {
        condfd = accept(sockfd,(struct sockaddr *)&clientaddr,&len);

        pid = fork();

        switch(pid)
        {
            case -1:
                perror("fork");
                return -1;
            case 0:
                close(sockfd);
                while(1)
                {
                    reval = recv(condfd,&info, sizeof(info),0);

                    if(reval == -1)
                    {
                        perror("recv");
                        return -1;
                    }
                    if(reval == 0)
                    {
                        printf("ip:%s已退出客户端！\n",inet_ntoa(clientaddr.sin_addr));
                        return 0;
                    }
                    if(reval > 0)
                    {
                       switch(info.choose)
                       {
                           case 1:
                               user_list(condfd,info);
                               break;
                           case 2:
                               user_down(condfd,info);
                               break;
                       }


                    }
                }
            default:
            {
                close(condfd);
            }
        }
    }
    return 0;
}
void user_list(int condfd, my_ftp_data_t info)
{
    //定义目录流指针
    DIR *pdir;

    struct dirent *rp;

    //清空原有的info.data[]里面的数据
    memset(info.data,0,sizeof(info.data));

    //打开目录
    pdir = opendir("/home/liuqi/Documents/network/network_3/server");
    //切换目录
    chdir("/home/liuqi/Documents/network/network_3/server");

    rp = readdir(pdir);
#if 0
    if(rp == NULL)
    {
        //rp返回值为NULL时,errno为EBADF,错误退出
        if(errno == EBADF)
        {
            perror("readdir");
            exit(EXIT_FAILURE);
        }
        else
        {
            //rp返回值没有errno号,说明该目录没有文件
            printf("该目录没有文件！\n");
        }
    }
    while(rp != NULL)
    {
        //去除隐藏文件
        if(rp->d_name[0] != '.')
            continue;
        //将文件名字传进info.data[]
        strcat(info.data,rp->d_name);
        //两个文件中间打一个空格
        info.data[strlen(info.data)] = ' ';

    }
#endif

#if 1
    while((rp = readdir(pdir)) != NULL)
    {
        if(rp->d_name[0] = '.')
            continue;
        strcat(info.data,rp->d_name);
        info.data[strlen(info.data)] = ' ';
        //将所有的文件名信息发送给客户端
        printf("%s\n",info.data);

    }
    send(condfd,&info,sizeof(info),0);
#endif
}


void user_down(int condfd, my_ftp_data_t info)
{
    char path[32];
    FILE *fp;
    //将接收到的文件名所在的路径存放到path数组中
    sprintf(path,"/home/liuqi/Documents/network/network_3/server/%s",info.fname);
    //打开目标文件
    fp = fopen(path,"r");
    //判断该目标文件是否存在
    if(fp == NULL)
    {
        perror("fopen");
        //将打开文件失败的标志位发送给客户端
        info.flag = FALSE;
        send(condfd,&info,sizeof(info),0);
        exit(EXIT_FAILURE);
    }
    else
    {
        //将打开文件成功的标志位发送给客户端
        info.flag = TRUE;
        send(condfd,&info,sizeof(info),0);
    }
    memset(info.data,0, sizeof(info.data));
    while(1)
    {
        //开始读取文件内的数据到结构体
        info.len = fread(info.data,1, sizeof(info.data),fp);
        //发送数据
        send(condfd,&info,sizeof(info),0);
        //判断文件内数据是不是最后一次循环
        if(info.len < sizeof(info.data))
            break;
    }
    fclose(fp);

}

