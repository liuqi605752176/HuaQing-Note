#include "cgic.h"
#include <string.h>

int cgiMain()
{
	//content-type
	cgiHeaderContentType("text/html");

	char buf[128]={0};

	cgiFormString("user",buf,sizeof(buf));
	//1.输入域类型名
	//2.结果数组首地址
	//3. 数组大小   实际最大字符 == 数组大小 -1




	//<html>....
	//printf???    
	//fprintf  --> cgiOut   
	fprintf(cgiOut,"<html><head><meta charset=""UTF-8""><title>谢宇星大坏蛋</title>");
	fprintf(cgiOut,"<body>");
	if(strncmp(buf,"谢宇星",strlen("谢宇星"))==0)
		fprintf(cgiOut,"<H1>%s 是彻彻底底的坏银！！！</H1>\n",buf);
	else
		fprintf(cgiOut,"<H1>%s 是大好银！！！</H1>\n",buf);

	fprintf(cgiOut,"</body></html>");


}
