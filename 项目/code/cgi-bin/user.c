#include <stdio.h>
#include "cgic.c"
#include "cgic.h"
#include "denglu.c"
#include "zhuce.c"

#define N 20

char name[N];
char pswd[N];

int cgiMain()
{
	cgiFormStringNoNewlines("username",name,N);
	cgiFormStringNoNewlines("userpassword",pswd,N);
	cgiHeaderContentType("text/html\n\n");
	fprintf(cgiOut, "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />");
	fprintf(cgiOut,"<html>");
	fprintf(cgiOut,"<head>");
	fprintf(cgiOut,"</head>");
	if(cgiFormSubmitClicked("button1") == cgiFormSuccess)
	{
		fprintf(cgiOut,"<body>");
		fprintf(cgiOut,"%s","denglu!!");
		int ret1 = denglu(name,pswd);
		fprintf(cgiOut,"%d",ret1);
		fprintf(cgiOut,"<br>");
		fprintf(cgiOut,"</body>");
		if(ret1 == -1)
		{
			fprintf(cgiOut,"登录失败！！！-1");
			fprintf(cgiOut,"<meta http-equiv=\"refresh\" content=\"1; url=../user.html\">");

		}else if(ret1 == -2)
		{
			fprintf(cgiOut,"登录失败！！-2");
			fprintf(cgiOut,"<meta http-equiv=\"refresh\" content=\"1; url=../user.html\">");

		}else if(ret1 == -3)
		{
			fprintf(cgiOut,"用户名与密码不匹配！！");
			fprintf(cgiOut,"<meta http-equiv=\"refresh\" content=\"1; url=../user.html\">");

		}
		if(ret1 == 1)
		{
			fprintf(cgiOut,"登录成功！！");
			fprintf(cgiOut,"<meta http-equiv=\"refresh\" content=\"1; url=../choose.html\">");
		}
		fprintf(cgiOut,"</html>");
	}
	if(cgiFormSubmitClicked("button2") == cgiFormSuccess)
	{
		fprintf(cgiOut,"<body>");
		fprintf(cgiOut,"%s","zhuce!!");
		int ret2 = zhuce(name,pswd);
		//	fprintf(cgiOut,"%d",ret2);
		fprintf(cgiOut,"<br>");
		fprintf(cgiOut,"</body>");
		if(ret2 == -1)
		{
			fprintf(cgiOut,"注册失败！！！-1");
			fprintf(cgiOut,"<meta http-equiv=\"refresh\" content=\"1; url=../user.html\">");

		}else if(ret2 == -2)
		{
			fprintf(cgiOut,"注册失败！！！-2");

			fprintf(cgiOut,"<meta http-equiv=\"refresh\" content=\"1; url=../user.html\">");
		}else if(ret2 == -3)
		{
			fprintf(cgiOut,"用户名已存在！！！");

			fprintf(cgiOut,"<meta http-equiv=\"refresh\" content=\"1; url=../user.html\">");
		}else if (ret2 == 1)
		{
			fprintf(cgiOut,"注册成功！！！\n");
			fprintf(cgiOut,"<meta http-equiv=\"refresh\" content=\"1; url=../choose.html\">");
		}

		fprintf(cgiOut,"</html>");
	}


}