#define  LOG_TAG  "hw_led"
#include <hardware/hardware.h>
#include <utils/Log.h>
#include  "led.h"
int  hw_c_open(struct  led_device_t  *  led_device)
{

	ALOGI("hw_c_open   \n");

	return  0;

}
int  hw_c_ioctl(struct  led_device_t  * led_device , int which,int status)
{

	ALOGI("hw_c_ioctl which  = %d,status  = %d\n",which,status);
	return  0;

}
struct  led_device_t   led_device  = {

	.common  = {
		
	
	},
	.hw_open  = hw_c_open,
	.hw_ioctl = hw_c_ioctl,


};

int hw_module_open(const struct hw_module_t* module, const char* id,struct hw_device_t** device)
{

	*device  = &led_device;		

	return  0;
}
struct hw_module_methods_t  hw_module_method  = {
 
	.open  = hw_module_open, 
 
 };
struct hw_module_t   HMI  =  {


	.id  = "led",
	.methods   =  &hw_module_method,



};
