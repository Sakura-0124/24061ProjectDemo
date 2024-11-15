#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/ioctl.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/io.h>
#include <linux/spinlock.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>
#include <linux/kernel.h>
#include <linux/sysfs.h>
#include <linux/kobject.h>

#include "led.h"

MODULE_LICENSE("GPL");

struct led_device
{
	dev_t devno;//设备号
	int   gpio;//GPIO引脚编号
	int   trigger_level;//电平
	struct cdev cdev;//字符设备
	struct class *cls;//设备类
	struct device *dev;//sysfs设备
};

//sysfs读操作
static int exynos_led_sysfs_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	//获取设备数据
	struct led_device *pled = dev_get_drvdata(dev);
	//获取gpio引脚电平
	int level = gpio_get_value(pled->gpio);
	return sprintf(buf, "%d\n", level);
}

//sysfs写操作
static ssize_t exynos_led_sysfs_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	//获取设备数据
	struct led_device *pled = dev_get_drvdata(dev);
	int level;
	
	//将用户输入的字符串转换为整数，表示gpio电平
	if (kstrtoint(buf, 10, &level) < 0)
	{
		return -EINVAL;
	}

	//设置gpio引脚电平
	gpio_set_value(pled->gpio, level);
	return count;
}

//设备属性定义，允许读写操作
static DEVICE_ATTR(led, 0777, exynos_led_sysfs_show, exynos_led_sysfs_store);

int exynos_led_open(struct inode *inode, struct file *file)
{
	struct led_device *pled = container_of(inode->i_cdev,struct led_device,cdev);
	printk("open success");
	file->private_data = pled;

	return 0;
}

//释放LED设备
int exynos_led_release(struct inode *inode, struct file *file)
{
	struct led_device *pled = container_of(inode->i_cdev,struct led_device,cdev);

	//关闭LED灯
	gpio_direction_output(pled->gpio,!pled->trigger_level);
	
	return 0;
}

//定义文件操作函数
struct file_operations exynos_led_fops = {
	.owner   = THIS_MODULE,
	.open    = exynos_led_open,
	.release = exynos_led_release,
	.unlocked_ioctl = exynos_led_ioctl,
};

//初始化并注册led设备
static int  exynos_led_probe(struct platform_device *pdev)
{
	int ret;
	struct led_device *pled;
	struct device_node *led_node = pdev->dev.of_node;
	
	printk("match\n");

	printk("pdev->name : %s\n",pdev->name);

	//动态分配led_device内存
	pled = devm_kzalloc(&pdev->dev,sizeof(struct led_device),GFP_KERNEL);
	if (!pled){
		printk("Fail to malloc memory for pled\n");
		return -ENOMEM;
	}

	//将pled指针储存为平台设备的驱动程序数据
	platform_set_drvdata(pdev, pled);


	//获取led灯对应的GPIO口
	/*
	 *@led_node   					: 设备树的节点对应的结构体(struct device_node)地址
	 *@led-gpio   					: gpio的属性名称
	 *@0          					: 这个设备的第一个gpio 
	 *@flags      					: 获取设备树的gpio描述的标志
	 <p align="justify"> *return    : 返回的是gpio的编号
	*/
	pled->gpio = of_get_named_gpio_flags(led_node,"led-gpio",0,(enum of_gpio_flags *)&pled->trigger_level);
	printk("os gpio number:%d\n",pled->gpio);
	
	//判断是否是有效的GPIO口
	if(!gpio_is_valid(pled->gpio)){
		printk("invalid led-gpios:%d\n",pled->gpio);
		return -ENODEV;
	}

	//请求占用GPIO
	ret = devm_gpio_request(&pdev->dev,pled->gpio,"led-gpios");
	if (ret){
		printk("Failed GPIO request for GPIO %d: %d\n",pled->gpio, ret);
		return ret;
	}

	//注册led_device到系统
	ret = register_led_device(pdev);
	if(ret < 0){
		printk("Fail to register led device!\n");
		return ret;
	}
		
	return 0;
}

//从系统中删除led设备驱动程序
static int exynos_led_remove(struct platform_device *pdev)
{
	//获取led设备
	struct led_device *pled = platform_get_drvdata(pdev);
	
	printk("led_remove: device remove\n");

	//销毁设备
	device_destroy(pled->cls,pled->devno);

	//销毁与led设备关联的类对象
	class_destroy(pled->cls);

	//删除字符设备
	cdev_del(&pled->cdev);

	//注销字符设备区域
	unregister_chrdev_region(pled->devno,1);

	return 0;
}

#if defined(CONFIG_OF)

//匹配设备树中的compatible属性
static const struct of_device_id exynos_led_dt_ids[] = {
	{ .compatible = "fs4412-led-gpio" },
	{ /* sentinel */ }
};

MODULE_DEVICE_TABLE(of, exynos_led_dt_ids);

#endif

static struct platform_driver exynos_led_driver = {
	.probe		= exynos_led_probe,
	.remove     = exynos_led_remove,
	.driver		= {
		.owner	= THIS_MODULE,
		.name	= "exynos-led",
		.of_match_table = of_match_ptr(exynos_led_dt_ids),
	},
};

int __init led_init(void)
{
	int ret;
	
	printk("Register led driver to platfrom bus!\n");

	ret = platform_driver_register(&exynos_led_driver);
	
	return ret;	
}

void __exit led_exit(void)
{
	printk("Remove led driver to platfrom bus!\n");
	
	platform_driver_unregister(&exynos_led_driver);
	return;
}

module_init(led_init);
module_exit(led_exit);
