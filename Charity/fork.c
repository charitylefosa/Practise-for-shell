#include<stdio.h>
#include<unistd.h>

int main(void)
{
	pid_t pid;
	pid_t ppid;

	pid = fork();
	if (pid == -1)
	{
		printf("Unsuccessful\n");
		return (1);
	}
	if (pid == 0)
	{
		sleep(5);
		printf("Successful\n");
	}
	else
	{
		ppid = getpid();
		printf("%u, %u\n", pid, ppid);
	}
	return (0);
}
