#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <linux/slab.h>
asmlinkage int sys_set_tag(int pid, char* tag, unsigned int length)
{
	printk(" ~~~ sys set tag START ~~~ \n");
	struct task_struct *task;

	task = find_task_by_vpid(pid);

	if(!task)
	{
		printk("No task with pid : %d\n",pid);
		return -1;
	}
	printk("found task!\n");

	char* temp = kmalloc(length+1, GFP_KERNEL); // add 1 for null
	if(!temp)
	{
		printk("tag malloc error!\n");
		return -2;
	}
	temp[length] = NULL;
	
	//reset tag
	if(task->tag)
	{
		kfree(task->tag);
	}
	task->tag = temp;

	// copy without memory allocation.
	if( 0 != copy_from_user(task->tag, tag, length) )
	{
		printk("copy_from_user failed\n");
		return -3;
	}

	printk("got tag, %s\n",task->tag);
	
	printk(" ~~~ sys set tag END ~~~ \n");
	return 0;
}
