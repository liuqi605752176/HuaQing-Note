#include "exynos_4412.h"


void init_timer()
{

	PWM.TCFG0 = (PWM.TCFG0 & ~(0XFF << 0)) | (99 << 0); // 100M/(99 +1) = 1M
	PWM.TCFG1 = (PWM.TCFG1 & ~(0XF << 0)) | (0B0010 << 0); // timer0 的工作频率 1M / 4 = 250Khz 每秒计数250000 次


	PWM.TCON = (PWM.TCON & ~(0XF << 0)) | (0B0000 << 0);// RELOAD = 0 UPDATE = 0 START = 0

	PWM.TINT_CSTAT = (PWM.TINT_CSTAT & ~(0B11111 << 5)) | (1 << 0); //启动timer4 中断

	//37 69  –  TIMER0
	ICDISR .ICDISR2 &= ~(1 << 7);
	ICDISER .ICDISER2 = (1 << 7);
	ICDIPR .ICDIPR17 = (ICDIPR .ICDIPR17 & ~(0xff << 8)) | (1 << 8); //优先级设置为 1
	
	ICDIPTR .ICDIPTR17 = (ICDIPTR .ICDIPTR17 & ~(0xff << 8))
			| (0b00000001 << 8);	//设置将中断送到icc0

	ICDDCR = 1;  //启动 icd
	CPU0 .ICCICR = 1; //使能icc

}

int  key_number;
void start_timer0(int fre)
{
	PWM.TCNTB0 = 250000 / fre - 1; //计数总周期 ： （1 / 250K） * 250000 = 1S  ：即 timer启动1s后会产生中断
	PWM.TCMPB0 = 250000 / fre / 2;

	PWM.TCON = (PWM.TCON & ~(0XF << 0)) | (0B0110 << 0);// RELOAD = 1 UPDATE = 1 START = 0
	PWM.TCON = (PWM.TCON & ~(0XF << 0)) | (0B0100 << 0);// RELOAD = 1 UPDATE = 0 START = 0
	PWM.TCON = (PWM.TCON & ~(0XF << 0)) | (0B0001 << 0);// RELOAD = 0 UPDATE = 0 START = 1


}
