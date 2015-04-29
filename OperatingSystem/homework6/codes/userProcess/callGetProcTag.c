#include <stdio.h>
#include <string.h>

void main()
{
	int pid;
	char tag[32] = "";

	printf("pid = ");
	scanf("%d",&pid);

	int length = syscall(341, pid, tag, strlen(tag));

	if(length < 0)
		printf("error\n");
	else
		printf("success, %s\n",tag);
	return;
}
