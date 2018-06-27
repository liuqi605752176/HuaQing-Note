#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
	int *data;//存数据
	int size;//存数据元素个数
	int top;//标记栈顶数据元素的位置
}stack_tt;//栈的数据类型

stack_tt * creat_stack(int size)
{
	stack_tt * stack = malloc(sizeof(stack_tt));
	if(stack == NULL)
	{
		return NULL;
	}
	stack->data = malloc(sizeof(int)*size);
	if(stack->data == NULL)
	{
		return NULL;
	}

	stack->size = size;

	stack->top = -1;

	return stack;
}

//判满
int isfull(stack_tt * stack)
{
	return stack->top == (stack->size - 1);
}

//判空
int isnull(stack_tt * stack)
{
	return stack->top == -1;
}

//增加数据
int push_stack(stack_tt * stack, int data)
{
	if(isfull(stack))
	{
		return -1;
	}
	
	//增加数据
	stack->data[stack->top+1] = data;

	//修改top位置
	stack->top++;

	return 0;
}

//删除数据
int pop_stack(stack_tt * stack, int *data)
{
	//判断实施条件
	if(isnull(stack))
	{
		return -1;
	}
	
	//获取出栈数据
	*data = stack->data[stack->top];

	//删除数据，修改top的位置
	stack->top--;

	return 0;
}

//获取栈顶数据
int get_stack_top(stack_tt * stack, int *data)
{
	//判断实施条件
	if(isnull(stack))
	{
		return -1;
	}

	//获取栈顶数据
	*data = stack->data[stack->top];

	return 0;
}

//打印数据
int print_stack(stack_tt * stack)
{
	//判断实施条件
	if(isnull(stack))
	{
		return -1;
	}

	int i;
	printf("栈顶\n");
	for(i = stack->top; i >= 0; i--)
	{
		printf("%d\n", stack->data[i]);
	}
	printf("栈底\n");

	return 0;
}

//清空
int clean_stack(stack_tt * stack)
{
	stack->top = -1;
	return 0;
}

//销毁
int dis_stack(stack_tt * stack)
{
	free(stack->data);
	free(stack);

	return 0;
}

int main(int argc, const char *argv[])
{
	stack_tt * stack = creat_stack(10);

	int i;
	for( i = 1; i <= 10; i++)
	{
		push_stack(stack, i * 10);
	}
	print_stack(stack);


	int data;
	for(i = 1; i <= 3; i++)
	{
		pop_stack(stack,&data);
		printf("data: %d\n", data);
		print_stack(stack);
	}

	int get_data;
	get_stack_top(stack, &get_data);
	printf("get_data:%d\n", get_data);


	clean_stack(stack);

	dis_stack(stack);

	return 0;
}
