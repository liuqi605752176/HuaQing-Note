#include "cgic.h"


int cgiMain()
{
	//content-type
	cgiHeaderContentType("text/html");

	//<html>....
	//printf???    
	//fprintf  --> cgiOut   
	fprintf(cgiOut,"<html><head><meta charset=""UTF-8""><title>谢宇星大坏蛋</title>");
	fprintf(cgiOut,"<body>");
	fprintf(cgiOut,"<H1>hello world!</H1>\n");
	fprintf(cgiOut,"</body></html>");


}
