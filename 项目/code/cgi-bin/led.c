#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <errno.h>
#include "HEAD.h"
#include "cgic.h"
#include "cgic.c"

int cgiMain()
{
	key_t key;
	int msgid;	
	char ledbuf[16];
	int cmd;
	MSG msg_buf;

//	cgiFormString("store", sto_no, sizeof(sto_no));
	cgiFormStringNoNewlines("led", ledbuf, sizeof(ledbuf));

	cmd = atoi(ledbuf);

	memset(&msg_buf,0,sizeof(msg_buf));
	
	if((key = ftok("/dev",'3')) < 0)
	{
		perror("ftok");
		exit(1);
	}

	if((msgid = msgget(key, 0666)) < 0)
	{
		perror("msgget");
		exit(1);
	}
#if 1
	if (cmd == 1)
	{ 
		msg_buf.mytext[0] = 1;
	}
	else if(cmd == 0)
	{
		msg_buf.mytext[0] = 0;
	}
#endif

	msg_buf.type = 1;
	

	msgsnd(msgid, &msg_buf,sizeof(msg_buf), 0);

	cgiHeaderContentType("text/html");
	fprintf(cgiOut, "<HTML>\n");
	fprintf(cgiOut, "<TITLE>led</TITLE></HEAD>\n");
	fprintf(cgiOut, "<BODY bgcolor=\"#fffffffff\">\n");
	fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"2;url=../led.html\">");
	fprintf(cgiOut, "</BODY></HTML>\n");

	return 0;
}
