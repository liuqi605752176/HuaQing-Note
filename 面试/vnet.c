
#include <linux/module.h>
#include <linux/ioport.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/interrupt.h>
#include <linux/skbuff.h>
#include <linux/spinlock.h>
#include <linux/crc32.h>
#include <linux/mii.h>
#include <linux/of.h>
#include <linux/of_net.h>
#include <linux/ethtool.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/irq.h>
#include <linux/slab.h>

  struct net_device *ndev;

static netdev_tx_t     vndo_start_xmit (struct sk_buff *skb,struct net_device *dev)
{

	static  int  count  = 0;

	printk("tx %d  package  \n",++count);
	printk("%ld\n",dev->stats. tx_packets++);
	
	return   0;


}  

int     fs4412_ndo_init(struct net_device *dev)
{

	printk("fs4412_ndo_init  \n");
	return  0;

}

  struct net_device_ops   vnet_ops  = {
  
	  .ndo_init  = fs4412_ndo_init,
	  .ndo_start_xmit  = vndo_start_xmit,
  
  
  };
int fs4412_vnet_init(void)
{

	int ret;

	ndev  = alloc_netdev(0,"vnet%d",ether_setup);
	if(ndev  == NULL)
		return  -ENOMEM;


	 ndev->netdev_ops  = &vnet_ops;
	  ret = register_netdev(ndev);
	  if(ret  <  0)
	  {
	  
		  printk("register_netdev  fail  \n");
		  return ret;
	  }

	  return  0;
}

void  fs4412_vnet_exit(void)
{

	 free_netdev(ndev);
	  unregister_netdev(ndev);

}


module_init(fs4412_vnet_init);
module_exit(fs4412_vnet_exit);
MODULE_LICENSE("GPL");
