#ifndef _INPUT_KEY_H_
#define _INPUT_KEY_H_ 

#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/mutex.h>
#include <linux/timer.h>
#include <linux/wait.h>
#include <linux/fs.h>
#include <linux/input.h>

#define KEY_DT_PATH "/my_key" 
#define NAME "my_key"

struct irq_key_desc
{
	unsigned int irq;						//中断号
	unsigned int gpio;						//gpio引脚号
	unsigned int code;						//按键码
	volatile unsigned int key_push_cnt;		//按键按下的次数
	volatile unsigned int key_release_cnt;	//按键松开的次数
};

struct my_key_dev
{
	struct class *my_key_class;		//设备类
	struct device *my_key_device;	//设备结构体
	struct timer_list timer;		//计时器
	struct input_dev *key_input_dev;//输入设备的指针，管理输入设备
	struct irq_key_desc key_desc;	//按键的事件描述符，管理按键的硬件资源
};

#endif 

