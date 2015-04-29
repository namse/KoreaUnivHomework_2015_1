#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
int g_my_queue[100];
int g_queue_count;

asmlinkage void sys_my_enqueue(int a)
{
	int i;
	g_my_queue[g_queue_count] = a;
	++g_queue_count;

	printk("Enqueue : [count : %d] ", g_queue_count);
	for(i = 0 ; i < g_queue_count; i++)
	{
		printk("%d ", g_my_queue[i]);
	}
	printk("\n"); 
}

asmlinkage int sys_my_dequeue(void)
{
	int ret, i;
	if( g_queue_count <= 0 )
	{
		return 0;
	}
	
	ret = g_my_queue[0];
	
	// shift left
	for(i = 0 ; i < g_queue_count - 1; i++)
	{
		g_my_queue[i] = g_my_queue[i+1];
	}

	--g_queue_count;
	
	printk("Dequeue : [count : %d] ", g_queue_count);
	for(i = 0 ; i < g_queue_count; i++)
	{
		printk("%d ", g_my_queue[i]);
	}
	printk("\n");
	return ret;
}
