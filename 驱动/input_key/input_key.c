#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/stat.h>
#include <linux/sysfs.h>
#include <linux/interrupt.h>
#include <linux/jiffies.h>
#include <linux/sched.h>  
#include <asm/io.h>
#include <linux/gpio.h> 
#include <linux/poll.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <linux/platform_device.h>
#include "my_key_input.h"


MODULE_LICENSE("GPL");

static struct my_key_dev *my_key = NULL;

irqreturn_t my_key_irq_handler(int irq, void *dev)
{
	struct my_key_dev *key = (struct my_key_dev*)dev;
	mod_timer(&key->timer, jiffies + msecs_to_jiffies(10));//加10毫秒延迟
	return IRQ_RETVAL(IRQ_HANDLED);
}

void timer_fun(unsigned long data)
{
	int val = 0;
	struct my_key_dev* dev  = (struct my_key_dev*)data;	//将data强转为my_key_dev类型
	val = gpio_get_value(dev->key_desc.gpio);			//获取gpio引脚值，0表示松开，1表示按下

	//按键按下
	if(val == 1)
	{
		input_report_key(dev->key_input_dev, dev->key_desc.code, val);
		input_sync(dev->key_input_dev);	//同步输入设备
		dev->key_desc.key_push_cnt++;	//记录按下次数
	}
	else//按键松开
	{
		input_report_key(dev->key_input_dev, dev->key_desc.code, val);
		input_sync(dev->key_input_dev);		//同步输入设备
		dev->key_desc.key_release_cnt++;	//记录松开次数
	}
}

//初始化按键gpio,设置中断
static int key_gpio_init(struct my_key_dev *dev, struct platform_device *pdev)
{
	int ret = 0;
	struct device_node *n;

	//获取按键设备树节点
	n = of_find_node_by_path(KEY_DT_PATH);//根据设备树路径查找节点
	if(NULL == n)
	{
		printk(KERN_ERR "find key node error by %s\n", KEY_DT_PATH);
		return -EINVAL;
	}

	//获取按键的gpio编号
	dev->key_desc.gpio = of_get_named_gpio(n, "key", 0);//从设备树获取gpio编号
	if(dev->key_desc.gpio < 0)
	{
		printk(KERN_ERR "can't get key number\n");
		return -EINVAL;
	}

	//请求gpio
	ret = gpio_request(dev->key_desc.gpio, NAME);//申请gpio资源
	if(ret < 0)
	{
		printk(KERN_ERR "request key gpio error\n");
		return -EINVAL;
	}

	gpio_direction_input(dev->key_desc.gpio);//将gpio设置为输入模式

	//获取IRQ(中断号)
	dev->key_desc.irq = irq_of_parse_and_map(n, 0);//解析并映射设备树中的IRQ
	if(0 == dev->key_desc.irq)
	{
		printk(KERN_ERR "can't parse and map irq\n");
		ret = -1;
		goto free_gpio;
	}

	//读取code的属性值
	ret = of_property_read_u32_index(n, "code", 0, &dev->key_desc.code);
	if(ret < 0)
	{
		printk(KERN_ERR "can't parse and map irq\n");
		goto free_gpio;
	}

	//请求中断
	ret = request_irq(dev->key_desc.irq, my_key_irq_handler, IRQ_TYPE_EDGE_BOTH, NAME, dev);
	if(ret < 0)
	{
		printk(KERN_ERR "request %s irq failed\n", NAME);
		goto free_gpio;
	}
	
	return 0;
	
free_gpio:
	gpio_free(dev->key_desc.gpio);
	return ret;
}

//初始化和注册按键设备
static int my_key_probe(struct platform_device *dev)
{
	int ret = 0;

	//分配设备结构体内存并将分配的内存清0
	my_key = kzalloc(sizeof(struct my_key_dev), GFP_KERNEL);
	if(NULL == my_key)
	{
		printk(KERN_ERR "kzalloc failed\n");
		return -ENOMEN;
	}

	init_timer(&my_key->timer);	//初始化定时器
	my_key->timer.function = timer_fun;
	my_key->timer.data = (unsigned long)my_key;
	add_timer(&my_key->timer);	//注册定时器

	ret = key_gpio_init(my_key, dev);	//初始化gpio和中断
	if(ret < 0) goto timer_del;		//初始化失败跳转删除定时器

	//分配input_dev结构体
	my_key->key_input_dev = input_allocate_device();	
	if(NULL == my_key->key_input_dev)
	{
		printk(KERN_ERR "allocate input device failed\n");
		ret = -ENOMEN;
		goto timer_del;
	}

	my_key->key_input_dev->name = NAME;				//设置设备名称
	set_bit(EV_KEY, my_key->key_input_dev->evbit);	//产生按键事件
	set_bit(EV_REP, my_key->key_input_dev->evbit);	//产生重复事件

	//产生key_0按键
	set_bit(my_key->key_desc.code, my_key->key_input_dev->keybit);

	//注册输入设备
	ret = input_register_device(my_key->key_input_dev);
	if(ret < 0)
	{
		printk(KERN_ERR "input device register failed\n");
		goto free_input_device;
	}
	
	printk(KERN_INFO "my_key module init OK\n");
	return 0;

free_input_device:
	input_free_device(my_key->key_input_dev);
timer_del:
	del_timer(&my_key->timer);	//删除定时器
	kfree(my_key);				//释放设备结构体内存
	my_key = NULL;
	return ret;
}


static int my_key_remove(struct platform_device *dev)
{
	input_unregister_device(my_key->key_input_dev);	//注销输入设备
	input_free_device(my_key->key_input_dev);		//释放输入设备
	gpio_free(my_key->key_desc.gpio);				//释放gpio引脚
	free_irq(my_key->key_desc.irq, my_key);			//释放IRQ资源
	del_timer(&my_key->timer);						//删除定时器
	kfree(my_key);									//释放设备结构体内存
	my_key = NULL;
	printk(KERN_INFO "my_key module exit\n");
	return 0;
}

//定义设备和驱动匹配需要的of_device_id匹配表变量
static const struct of_device_id my_key_of_match[] = {
	{.compatible = "my_key"},	//兼容属性，需要与设备树中的兼容属性一致
		{/*sentinel*/}
};	

MODULE_DEVICE_TABLE(of, my_key_of_match);

//定义注册驱动时需要的platform_driver结构体变量
static struct platform_driver my_key_platform_driver = {
	.driver = {
		.name = "key",						//设置驱动的名称
		.of_match_table = my_key_of_match,	//驱动的设备的匹配数组信息，一个驱动可以和多个设备匹配
		},
	.probe = my_key_probe,		//设置初始化probe函数，驱动和设备匹配成功后此函数会执行
	.remove = my_key_remove,	//设置退出remove函数
};

static int __init my_key_init(void)
{
	int ret;
	
	printk("Register my_key driver to platfrom bus!\n");

	ret = platform_driver_register(&my_key_platform_driver);
	
	return ret;	
}

static void __exit my_key_exit(void)
{
	printk("Remove my_key driver to platfrom bus!\n");
	
	platform_driver_unregister(&my_key_platform_driver);
	return;
}

module_init(my_key_init);
module_exit(my_key_exit);
