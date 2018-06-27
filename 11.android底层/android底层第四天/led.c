
#include  <linux/module.h>
#include <linux/fs.h>
#include <asm/io.h>
#include <linux/leds.h>
#include <linux/slab.h>


#define GPFCON 0x01C208B4
#define GPFDAT 0x01C208C4

unsigned  int  *  gpf2con;
unsigned  int  *  gpf2dat;


struct  led_classdev   *fs_dev;

 void        fspad733_brightness_set(struct led_classdev *led_cdev, enum led_brightness brightness)
{
	if(brightness  ==  LED_OFF)
	{
	
		writel(readl(gpf2dat) |(0x1 <<2),gpf2dat);
	}else{
	
		
	writel(readl(gpf2dat) &~(0x1 <<2),gpf2dat);
	
	
	}


}
static  int   fspad733_led_init(void)
{

	int ret;

	fs_dev   =  kzalloc(sizeof(struct  led_classdev),GFP_KERNEL);
	if(NULL  ==  fs_dev)
	{
	
		printk("kzalloc  fail  \n");
		return  -ENOMEM;
	
	}
	fs_dev->name   = "led6";

	fs_dev->flags   =  LED_CORE_SUSPENDRESUME;
	fs_dev->brightness_set  = fspad733_brightness_set;
	

	gpf2con  = ioremap(GPFCON,0x4);
	gpf2dat  = ioremap(GPFDAT,0x4);
	writel((readl(gpf2con) &~(0xf <<8))|(0x1 <<  8),gpf2con);
	writel(readl(gpf2dat) &~(0x1 <<2),gpf2dat);
	
	ret  = led_classdev_register(NULL,fs_dev);
	if(ret  <  0)
	{
	
		printk("led_classdev_register  fail  \n");
		kfree(fs_dev);
		return  ret;
	
	}

	return   0;

}

static  void  fspad733_led_exit(void)
{

	led_classdev_unregister(fs_dev);
	kfree(fs_dev);

}


module_init(fspad733_led_init);
module_exit(fspad733_led_exit);
MODULE_LICENSE("GPL");
