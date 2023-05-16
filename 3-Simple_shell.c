#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include"main.h"

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64


void read_prompt(char *command)
{
	printf("$ ");
	fflush(stdout);
	fgets(command, MAX_COMMAND_LENGTH, stdin);
}

void print_env(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}
int write_command(char *command, char **args)
{
	int i = 0;
	char *token;

	token = strtok(command, " ");
	while (token != NULL && i < MAX_ARGS - 1)
	{
		args[i] = token;
		token = strtok(NULL, " ");
		i++;
	}
	args[i] = NULL;
	return (i);
}

void execute_command(char **args)
{
	pid_t pid;

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


int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	char *args[MAX_ARGS];
	int running = 1;
	int argc;

	while (running)
	{
		read_prompt(command);
		command[strcspn(command, "\n")] = '\0';
		argc = write_command(command, args);
		if (argc > 0)
		{
			if (strcmp(args[0], "env") == 0)
			{
				print_env();
				continue;
			}
			if (strcmp(args[0], "exit") == 0)
				exit(EXIT_SUCCESS);
			else
				execute_command(args);
		}
	}
	return (0);
}
