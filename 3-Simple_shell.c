#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64

extern char **environ;

void print_env()
{
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}

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
		if (strcmp(args[0], "env") == 0)
		{
			print_env();
			continue;
		}
		if (strcmp(args[0], "exit") == 0)
		{
			exit(EXIT_SUCCESS);
		}
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
