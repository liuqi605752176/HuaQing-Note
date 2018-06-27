/*
 *@brief	This example describes how to use GPIO to drive LEDs
 *@date:	02. June. 2014
 *@author	liujh@farsight.com.cn
 *@Contact 	Us: http://dev.hqyj.com
 *Copyright(C) 2014, Farsight
*/

#include "exynos_4412.h"


/**********************************************************************
 * @brief		mydelay_ms program body
 * @param[in]	int (ms)
 * @return 		None
 **********************************************************************/
void mydelay_ms(int ms)
{
	int i, j;
	while(ms--)
	{
		for (i = 0; i < 5; i++)
			for (j = 0; j < 514; j++);
	}
}

void do_irq()
{
	//读取中断号，通知CPU处理中断函数
	int irq_number;
	irq_number = CPU0.ICCIAR & 0x3FF;
	printf("%d\n",irq_number);
	printf("key2");
	//清除中断源
	EXT_INT41_PEND = (1 << 1);
	//清除中断控制器状态
	CPU0.ICCEOIR = (CPU0.ICCEOIR & ~0x3FF) | irq_number;
}

int main(void)
{
	/*
	 *Config
	 */
	//KEY2初始化
	//KEY2 = GPX1_1 外部中断模式EXT_INT41[1]

	//GPX1CON[1]4位清0，并设置为外部中断模式
	GPX1.CON = (GPX1.CON & ~(0xF << 4)) | (0xF << 4);

	//配置EXT_INT41[1]的外部中断
	EXT_INT41_CON = (EXT_INT41_CON & ~(0xF << 4)) | (0x2 << 4);
	//配置滤波
	EXT_INT41_FLTCON0 |= 1 << 15;
	//延时滤波
	EXT_INT41_FLTCON0 &= ~(1 << 14);
	//使能中断
	EXT_INT41_MASK &= ~(1 << 1);

	//配置中断ICD ICC ,中断ID 57
	//中断使能
	ICDDCR = 1;
	//中断安全 ICDISR1的第25位
	ICDISR.ICDISR1 &= ~(1 << 25);
	ICDISER.ICDISER1 |= (1 << 25);
	//中断优先级
	ICDIPR.ICDIPR14 = (ICDIPR.ICDIPR14 & ~(0xFF << 8)) | (1 << 8);
	//选择中断CPU
	ICDIPTR.ICDIPTR14 = (ICDIPTR.ICDIPTR14 & ~(0xFF << 8)) | (0b00000001 << 8);
	//中断类型

	//使能ICC
	CPU0.ICCICR = 1;


	/****************************************************/
	while (1);
	return 0;
}
