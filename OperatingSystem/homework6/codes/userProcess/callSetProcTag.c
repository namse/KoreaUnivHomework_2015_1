#include<stdio.h>
#include<string.h>
void main()
{
	int pid;
	char tag[32] = "";

	printf("pid : ");
	scanf("%d",&pid);

	printf("tag : ");
	scanf("%s",tag);

	int ret = syscall(340, pid, tag, strlen(tag));
	
	if(ret == 0)
		printf("successfully inserted\n");
	else
		printf("error! %d\n", ret);
	return;
}
