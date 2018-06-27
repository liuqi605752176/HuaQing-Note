#if 1
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
void mydelay_ms(int ms) {
	int i, j;
	while (ms--) {
		for (i = 0; i < 5; i++)
			for (j = 0; j < 514; j++)
				;
	}
}

void do_irq() {

}

int main(void) {

	uart_init();
	printf("hello world!\n");

///--------------------------------------------------------------

	//GPD0.PUD = GPD0.PUD & ~(0XF);


///-------------------------------------------------------------
	PWM.TCFG0 = (PWM.TCFG0 &~(0XFF << 0)) | (99 << 0);
	//  100MHz/(99 + 1) / 4 = 250000Hz
	PWM.TCFG1 = (PWM.TCFG1 & ~(0XF << 0)) | (0b0010 << 0);
	PWM.TCNTB0 = 956 - 1;
	PWM.TCMPB0 = 956 / 2;
	
	//PWM .TCON = (PWM .TCON & ~(0XFF)) | (0B01010); // DEAD = 0 RELOAD = 1 Inverter = 0  UPDATE = 1 START = 0
	//PWM .TCON = (PWM .TCON & ~(0XFF)) | (0B01000); // DEAD = 0 RELOAD = 1 Inverter = 0  UPDATE = 0 START = 0

	PWM.TCON = (PWM.TCON & ~(0XFF << 0)) | (1 << 0) | (1 << 3);

	GPD0.CON = GPD0.CON & ~(0XF) | (0x2);
///------------------------------------------------------------

	while (1)
	{
		//do
		PWM.TCNTB0 = 956 - 1;
		PWM.TCMPB0 = 956 / 2;
		//PWM.TCON = PWM.TCON & ~(0XF) | (1 << 0) | (1 << 3);
		mydelay_ms(500);
		//beep_off();
		//re
		PWM.TCNTB0 = 851 - 1;
		PWM.TCMPB0 = 851 / 2;
		//PWM.TCON = PWM.TCON & ~(0XF) | (1 << 0) | (1 << 3);
		mydelay_ms(500);
		//beep_off();
		//mi
		PWM.TCNTB0 = 758 - 1;
		PWM.TCMPB0 = 758 / 2;
		//PWM.TCON = PWM.TCON & ~(0XF) | (1 << 0) | (1 << 3);
		mydelay_ms(500);
		//beep_off();
		//fa
		PWM.TCNTB0 = 716 - 1;
		PWM.TCMPB0 = 716 / 2;
		//PWM.TCON = PWM.TCON & ~(0XF) | (1 << 0) | (1 << 3);
		mydelay_ms(500);
		//beep_off();

	}


	return 0;
}

#endif

#if 0
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
void mydelay_ms(int ms) {
	int i, j;
	while (ms--) {
		for (i = 0; i < 5; i++)
			for (j = 0; j < 514; j++)
				;
	}
}



void do_irq() {


}

int main(void) {

	uart_init();
	printf("hello world!\n");
	PWM .TCFG0 = (PWM .TCFG0 & ~(0XFF << 0)) | (99 << 0); // 100M/(99 +1) = 1M
	PWM .TCFG1 = (PWM .TCFG1 & ~(0XF << 0)) | (0B0010 << 0); // timer0 的工作频率 1M / 4 = 250Khz 每秒计数250000 次

	PWM .TCNTB0 = 478 - 1; // 计数250次  总周期1ms 频率 1Khz
	PWM .TCMPB0 = 478 / 2; // 占空比50%

	PWM .TCON = (PWM .TCON & ~(0XFF)) | (0B01010); // DEAD = 0 RELOAD = 1 Inverter = 0  UPDATE = 1 START = 0
	PWM .TCON = (PWM .TCON & ~(0XFF)) | (0B01000); // DEAD = 0 RELOAD = 1 Inverter = 0  UPDATE = 0 START = 0
	PWM .TCON = (PWM .TCON & ~(0XFF)) | (0B01001); // DEAD = 0 RELOAD = 1 Inverter = 0  UPDATE = 0 START = 1

	GPD0 .CON = (GPD0 .CON & ~(0XF)) | 0X2;  // 选择tout0 输出模式
											 //	0x0 = Input
											 //	0x1 = Output
											 //	0x2 = TOUT_0

	while (1) {
		PWM .TCNTB0 = 478 - 1; // 计数250次  总周期1ms 频率 1Khz
		PWM .TCMPB0 = 478 / 2; // 占空比50%

		mydelay_ms(500);

		PWM .TCNTB0 = 426 - 1; // 计数250次  总周期1ms 频率 1Khz
		PWM .TCMPB0 = 426 / 2; // 占空比50%
		mydelay_ms(500);

		PWM .TCNTB0 = 379 - 1; // 计数250次  总周期1ms 频率 1Khz
		PWM .TCMPB0 = 379 / 2; // 占空比50%
		mydelay_ms(500);
	}

	while (1)
		;
	return 0;
}


#endif
