#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024

int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	int running = 1;
	pid_t pid;

	while (running)
	{
		printf("$ ");
		if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
		{
			printf("\n");
			break;
		}
		command[strcspn(command, "\n")] = '\0';
		pid = fork();
		if (pid < 0)
		{
			fprintf(stderr, "Error: Fork failed.\n");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			execlp(command, command, NULL);
			fprintf(stderr, "Error: Command not found.\n");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
		}
	}
	return (0);
}
