#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
asmlinkage unsigned int sys_get_tag(int pid, char* tag, unsigned int maxLength)
{
	printk(" ~~~ sys get tag START ~~~ \n");

	unsigned int length;
	struct task_struct* task;

	task = find_task_by_vpid(pid);
	
	if(!task)
	{
		printk("No such task with pid : %d\n",pid);
		return -1;
	}

	printk("task found\n");

	length = strlen(task->tag);

	if( maxLength > length )
	{
		printk("Too short your buffer! %d/%d\n",length, maxLength);
		return -1;
	}

	if( 0 != copy_to_user(tag, task->tag, length) )
	{
		printk("copy_to_user fail\n");
		return -1;
	}
	
	printk("got tag, %s\n", task->tag);
	
	printk(" ~~~ sys get tag END ~~~ \n");
	return length;
}
