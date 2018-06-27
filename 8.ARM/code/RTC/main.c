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

	//清除中断源
	RTCINTP = 1 << 1;
	//清除中断控制器状态
	CPU0.ICCEOIR = (CPU0.ICCEOIR & ~0x3FF) | irq_number;

}


/*-------------------------MAIN FUNCTION------------------------------*/
/**********************************************************************
 * @brief		Main program body
 * @param[in]	None
 * @return 		int
 **********************************************************************/
int main(void)
{
	/*
	 *Config
	 */

	//使能RTC控制
	RTCCON = 1 << 0;

	//使能RTCALARM 一分钟闹钟
	RTCALM.ALM = 1 << 0 | 1 << 6;

	//初始化时分秒闹钟

	RTCALM.SEC = 0X30;
;

	//中断源ID  76
	//-----------------------配置中断控制器
	ICDDCR = 1;							//中断使能
	ICDISR.ICDISR2 &= ~(1 << 12);		//安全模式
	ICDISER.ICDISER2 |= (1 << 12);
	ICDIPR.ICDIPR19 = (ICDIPR.ICDIPR19 & ~(0XFF)) | (1 << 0);	//中断优先级
	ICDIPTR.ICDIPTR19 = (ICDIPTR.ICDIPTR19 & ~(0XFF)) | (0B00000001 << 0);
	CPU0.ICCICR = 1;	//使能ICC


	while(1)
	{


	}
	return 0;
}
