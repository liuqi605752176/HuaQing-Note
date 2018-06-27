
#include  <linux/module.h>
#include <linux/fs.h>
#include <asm/io.h>

#define GPFCON 0x01C208B4
#define GPFDAT 0x01C208C4

unsigned  int  *  gpf2con;
unsigned  int  *  gpf2dat;
int  marjor;

static  int  fspad733_led_open(struct inode  *  inode,struct  file  * file)
{

	printk("fspad733_led_open  \n");
	return  0;

}
static long fspad733_led_ioctl (struct file *file, unsigned int  cmd, unsigned long  arg)
{

	printk("cmd  = %d,arg  = %ld \n",cmd,arg);
	if(arg   == 1)
	{
	
		writel(readl(gpf2dat) &~(0x1  <<2),gpf2dat);

	
	}
	if(arg  == 0)
	{
	

	writel(readl(gpf2dat) |(0x1  <<2),gpf2dat);
	
	}
	return  0;

}
struct  file_operations  led_fops  = {

	.open  =  fspad733_led_open,
	.unlocked_ioctl  = fspad733_led_ioctl,


};
int  fspad733_led_init(void)
{

	marjor  = register_chrdev(0,"led",&led_fops);
	if(marjor  <  0)
	{
	
		printk("register_chrdev  fail  \n");
		return  -EBUSY;
	
	}
	printk("marjor  = %d\n",marjor);

	gpf2con  = ioremap(GPFCON,0x4);
	gpf2dat  = ioremap(GPFDAT,0x4);

	writel((readl(gpf2con) &~(0xf << 8))|(0x1  <<8),gpf2con);
	writel(readl(gpf2dat) &~(0x1  <<2),gpf2dat);
	return  0;
}

void  fspad733_led_exit(void)
{

	iounmap(gpf2con);
	iounmap(gpf2dat);
	unregister_chrdev(marjor,"led");


}


module_init(fspad733_led_init);
module_exit(fspad733_led_exit);
MODULE_LICENSE("GPL");
