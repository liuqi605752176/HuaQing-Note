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
	//LED2 GPX2_7
	GPX2.CON = GPX2.CON & ~(0xF << 28) | (1 << 28);
	//LED3 GPX1_0
	GPX1.CON = GPX1.CON & ~(0xF) | 0x01;
	//LED4 LED5 GPF3_4 GPF3_5
	GPF3.CON = GPF3.CON & ~(0xF << 16 | 0xF << 20) | (1 << 16 | 1 << 20);

	GPD0.CON = GPD0.CON & ~(0xF << 0) | 1 << 0;

	GPX2.DAT = ~(1 << 7);
	GPX1.DAT = ~(1 << 0);
	GPF3.DAT = ~(11 << 4);

	GPD0.DAT = 1 << 0;
	mydelay_ms(1000);
	GPD0.DAT = ~(1 << 0);

	while(1)
	{
		//LED2ÁÁ//LED5Ãð
		GPF3.DAT = ~(1 << 4);
		GPX2.DAT = 1 << 7;
		mydelay_ms(1000);

		//LED3ÁÁ  LED2Ãð
		GPX2.DAT = ~(1 << 7);
		GPX1.DAT = 1 << 0;
		mydelay_ms(1000);

		//LED4ÁÁ  LED3Ãð
		GPX1.DAT = ~(1 << 0);
		GPF3.DAT = 1 << 4;
		mydelay_ms(1000);

		//LED5ÁÁ  LED4Ãð
		GPF3.DAT = ~(1 << 4);
		GPF3.DAT = 1 << 5;
		mydelay_ms(1000);


	}
	return 0;
}
