#include <stdio.h>



int main(int argc, const char *argv[])
{
	int a[2][3] = {{1,2,3},{4,5,6}};
	int *p[2] = {a[0],a[1]};
	int i,j;
	int sum = 0;
	for(i = 0;i < 2;i++)
	{
		for(j = 0;j < 3;j++,p[i]++)
		{
			sum = sum + a[i][j];
		//	sum = sum + *p[i];
		}
	}

	printf("%d\n",sum);



	return 0;
}
