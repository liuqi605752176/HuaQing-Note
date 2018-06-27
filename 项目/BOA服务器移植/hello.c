#include <cgic.h>

int cgiMain()
{
	cgiContentType("text/html");
	fprintf(cgiOut,"<html><head><meta charset=""UTF-8"">");
	fprintf(cgiOut,"<body>");
	fprintf(cgiOut,"<H1>hello world!</H1>\n");
	fprintf(cgiOut,"</body></html>");
}