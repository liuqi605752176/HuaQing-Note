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
	GPX2.CON = (GPX2.CON & ~(0xF << 28)) | (0x1 << 28);
	GPX2.DAT &= ~(1 << 7);
	//LED3 GPX1_0
	GPX1.CON = (GPX1.CON & ~(0xF << 0)) | (0x1 << 0);

	GPX1.DAT |= 1;
	mydelay_ms(1000);
	GPX1.DAT &= ~1;

	//KEY3 GPX1_1
	GPX1.CON = (GPX1.CON & ~(0xF << 8));

	while(1)
	{
		if(GPX1.DAT & (0x1 << 2) == 0)
		{
			mydelay_ms(25);
			if ((GPX1.DAT & (0x1 << 2)) == 0)
			{
				GPX1.DAT ^= 1;
				while ((GPX1.DAT & (0x1 << 2)) == 0);
			}
							
			
		}
	}
	while (1);
	return 0;
}
