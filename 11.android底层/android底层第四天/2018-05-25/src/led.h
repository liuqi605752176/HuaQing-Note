#ifndef  __LED_H__
#define  __LED_H__

struct  led_device_t   {


	hw_device_t  common;
	int  (*hw_open)(struct  led_device_t  *led_device);
	int  (*hw_ioctl)(struct led_device_t  *led_device,int which,int status);



}; 

#endif 
