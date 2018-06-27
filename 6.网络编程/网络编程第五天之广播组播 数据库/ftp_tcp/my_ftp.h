//
// Created by liuqi on 4/11/18.
//

#ifndef NETWORK_3_MY_FTP_H
#define NETWORK_3_MY_FTP_H

#define FALSE 0
#define TRUE 1
#define PORT 50000
typedef struct ftp_data
{
    int choose;
    int flag;
    char data[128];
    char fname[15];
    size_t len;
}my_ftp_data_t;


#endif //NETWORK_3_MY_FTP_H
