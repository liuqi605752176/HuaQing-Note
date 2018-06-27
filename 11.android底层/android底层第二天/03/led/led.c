
#include  <linux/module.h>
#include <linux/fs.h>


int marjor;
static  int  fspad733_led_open(struct inode  *  inode,struct  file  * file)
{

	printk("fspad733_led_open  \n");
	return  0;

}
static long fspad733_led_ioctl (struct file *file, unsigned int  cmd, unsigned long  arg)
{

	printk("cmd  = %d,arg  = %ld \n",cmd,arg);
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

	return  0;
}

void  fspad733_led_exit(void)
{

	unregister_chrdev(marjor,"led");


}


module_init(fspad733_led_init);
module_exit(fspad733_led_exit);
MODULE_LICENSE("GPL");
