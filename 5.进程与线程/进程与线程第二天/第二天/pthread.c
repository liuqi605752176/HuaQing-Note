#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


pthread_t tid1,tid2;

void *fun1(void *args)
{

		printf("hello\n");
	//	sleep(1);
		sleep(5);

}

void *fun2(void *args)
{
	
	printf("world\n");
		//sleep(1);

}

int main(int argc, const char *argv[])
{
	
	if(0 != pthread_create(&tid1,NULL,fun1,NULL))
	{
		printf("pthread_create is fail\n");
		exit(1);
	}


	if(0 != pthread_create(&tid2,NULL,fun2,NULL))
	{
		printf("pthread_create is fail\n");
		exit(1);
	}

	if(0 != pthread_join(tid1,NULL))
	{
		printf("pthread_join is fail\n");
		exit(1);
	}

	if(0 != pthread_join(tid2,NULL))
	{
		printf("pthread_join is fail\n");
		exit(1);
	}
	return 0;
}
