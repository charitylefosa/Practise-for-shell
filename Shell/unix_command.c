#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

#define MAX_ARGS 10
#define BUFFER_SIZE 1024

void execute_command(char *command)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		execlp(command, command, NULL);
		perror("execlp");
	}
	if (pid > 0)
	{
		wait(NULL);
	}
	else
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
}

/*int write_command(char *command, char **args)
{
	int argc = 0;
	char *token;

	token = strtok(command, "\t\n");
	while (token != NULL)
	{
		args[argc] = token;
		argc++;
		token = strtok("NULL", "\t\n");
	}
	args[argc] = NULL;
	return (argc);
}*/

void read_command(char *command)
{
	putchar('$');
	putchar(' ');
	fgets(command, BUFFER_SIZE, stdin);
}

int main()
{
	char command[BUFFER_SIZE];

	while (1)
	{
		read_command(command);
		command[strcspn(command, "\n")] = '\0';
		if (strcmp(command, "exit") == 0)
		{
			exit(EXIT_SUCCESS);
		}
		else
		{
			execute_command(command);
		}
	}
	return (0);
}
