#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>

typedef struct msg
{
	char type;
	char name[15];
}msg_t;

int main(int argc, const char *argv[])
{
	int sockfd;
	pid_t pid;

	sockfd = socket(AF_INET,SOCK_DGRAM,0);

	struct sockaddr_in seraddr;

	memset(&seraddr,0,sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(50000);
	seraddr.sin_addr.s_addr = inet_addr("172.25.1.194");

	msg_t info;
	printf("请输入登录名称:");
	fgets(info.name,sizeof(info.name),stdin);
	info.name[strlen(info.name) - 1] = '\0';
	info.type = 'L';//控制类型是Ｌ
	sendto(sockfd,&info,sizeof(info),0,(const struct sockaddr *)&seraddr,sizeof(seraddr));

	pid = fork();
	if(pid == -1)
	{
		
	}
	else if(pid == 0)
	{
			
	}
	else
	{
		while(1)
		{
			recvfrom(sockfd,&info,sizeof(info),0,NULL,NULL);
			switch(info.type)
			{
			case 'L':
				printf("**********%s上线*********\n",info.name);
				break;
			}
		}
	}
	return 0;
}
