#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
int g_my_queue[100];
int g_queue_index;

asmlinkage void sys_my_enqueue(int a)
{
	g_my_queue[g_queue_index] = a;
	printk("enqueue, %d on index : %d",g_my_queue[g_queue_index], g_queue_index);
	++g_queue_index;
}

asmlinkage int sys_my_dequeue(void)
{
	if( g_queue_index <= 0 )
	{
		return 0;
	}
	printk("dequeue, %d on index : %d",g_my_queue[g_queue_index], g_queue_index);
	return g_my_queue[g_queue_index--];
}
