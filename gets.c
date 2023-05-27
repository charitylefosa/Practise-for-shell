#include "main.h"
/**
 * getspecial - wrap for getspecial static variable
 * Return: Address of shellvariable special
 */

ShellVar **getspecial()
{
	static ShellVar *special;
	return (&special);
}



ShellVar **getvars()
{
	static ShellVar *vars;
	return (&vars);
}
/**
 * _getpid - find PID of the current  process
 * Return: str of PID
 */

char *_getpid()
{
	char *s = NULL;
	char *pid = NULL;
	char *n;
	char *file = "/proc/self/status";
	int fd;
	size_t bufsize = 1024;

	s = malloc(bufsize);
	if (s == NULL)
		return (NULL);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		free(s);
		return (NULL);
	}
	while (_getline(&s, fd))
	{
		n = _strtok(s, ":");
		if (!_strcmp(n, "Pid"))
		{
			pid = _strtok(NULL, "\n \t");
			break;
		}
	}
	close(fd);
	free(s);
	return (pid);
}
