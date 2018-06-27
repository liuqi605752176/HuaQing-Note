#ifndef _HEAD_H
#define _HEAD_H

typedef struct mymsg {
	long   type;
	long   mytype;       /* Message type. */
	char   mytext[100];/* Message text. */
	int MAXtemp;
	int MINtemp;
	int MAXsd;
	int MINsd;
	int MAXlight;
	int MINlight;
}MSG;

//消息队列
	type = 1 : led 指令
	


typedef struct shmbuf
{
	int DH11_wd;
	int DH11_sd;
	int DO_led;
}SHM;










#endif
