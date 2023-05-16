#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64

int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	char *args[MAX_ARGS];
	int running = 1;
	pid_t pid;
	int i;
	char *token;

	while (running)
	{
		printf("$ ");
		if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
		{
			printf("\n");
			break;
		}
		command[strcspn(command, "\n")] = '\0';
		i = 0;
		token = strtok(command, " ");
		while (token != NULL && i < MAX_ARGS -1)
		{
			args[i] = token;
			token = strtok(NULL, " ");
			i++;
		}
		args[i] = NULL;
		if (i == 0)
			continue;
		pid = fork();
		if (pid < 0)
		{
			fprintf(stderr, "Error: Fork failed.\n");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			execvp(args[0], args);
			fprintf(stderr, "./shell: No such file or directory\n");
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
		}
	}
	return (0);
}
