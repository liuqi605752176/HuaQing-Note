#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "cgic.h"
#include "cgic.c"
#include "head.h"

int cgiMain()
{
	key_t key;
	int msgid;
	char buf[2];
	msgbuf_t msg_buf;

	int cmd;

	cgiFormString("led", buf, sizeof(buf));
	
	cgiHeaderContentType("text/html\n\n"); 
	fprintf(cgiOut, "<HTML><HEAD>\n"); 
	fprintf(cgiOut, "<TITLE>LED CGI</TITLE></HEAD>\n"); 
	fprintf(cgiOut, "<BODY>"); 

	cmd = buf[0];
	memset(&msg_buf, 0, sizeof(msg_buf));

	bzero (msg_buf.mtext, sizeof (msg_buf.mtext));

	if (cmd == LED_ON)
	{
		msg_buf.mtext[0] = '2';
		
	}
	

	else if(cmd == LED_OFF)
	{
		msg_buf.mtext[0] = '3';
	}

	printf(" led_snd cmd = %c\n",cmd);

	key = ftok("/dev",'i');
	if(-1 == key)
	{
	fprintf(cgiOut,"ftok error!");
		return -1;
	}
	
	msgid = msgget(key,IPC_CREAT|IPC_EXCL|0666);
	
	if(msgid == -1)
	{
		if(errno == EEXIST)
		{
			msgid = msgget(key,0666);
		}else
		{
//			perror("msgget");
		fprintf(cgiOut,"msgget error!");
			return 2;
		}
	}




	msg_buf.mtype = 100;
	fgets(msg_buf.text,sizeof(msg_buf.text),stdin);

	if(-1 == msgsnd(msgid,&msg_buf,MSGSIZE,0))
	{
//		perror("msgsnd");
	fprintf(cgiOut,"msgsnd error!");
		return 3;
	}

	fprintf(cgiOut, "<H2>send sucess</H2>");
	fprintf(cgiOut, "<H2></H2>");
	fprintf(cgiOut, "<meta http-equiv=\"refresh\"content=\"1;url=../led.html\">");
	fprintf(cgiOut, "</BODY>\n"); 
	fprintf(cgiOut, "</HTML>\n"); 	
	return 0;
}
