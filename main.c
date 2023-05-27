#include "main.h"

/**
* inputvalidator- validates buffer input
* @buf: buffer to be validated
* @fd: file descriptor
* Return: command value
*	negative numbers for syscall errors
*	2 for syntax errors
*/
int inputvalidator(char **buf, int fd)
{
	char *newbuf, *bufgl, *bufptr = *buf;
	ssize_t lenr;
	size_t linebuf;
	int start = 1, complete = 0;
	linecounter(1);
	if (*bufptr == 0)
		return (0);
	while (*bufptr)
	{
#ifdef DEBUGVALID
		printf("In valid loop complete: %d: bufptr: %s", complete, bufptr);
#endif
		while ((*bufptr == ' ' || *bufptr == '\n') && !(complete & 3))
bufptr++;
		if (*bufptr == 0)
			break;
		if (start)
		{
			if (*bufptr == ';' && *(bufptr + 1) == ';')
			{
				free(*buf);
				printerr(": Syntax error \";;\" unexpected\n");
				setsvar("0", "2");
				return (2);
			}
			if (*bufptr == ';')
			{
				free (*buf);
				printerr(": Syntax error \"&\" unexpected\n");
				setsvar("0", "2");
				return (2);
			}
			if (*bufptr == '&' && *(bufptr + 1) == '&')
			{
				free(*buf);
				printerr(": Syntax error \";;\" unexpected\n");
				setsvar("0", "2");
				return (2);
			}
			if (*bufptr == '&')
			{
				free (*buf);
				printerr(": Syntax error \"&\" unexpected\n");
				setsvar("0", "2");
				return (2);
			}
			if (*bufptr == '|' && *(bufptr + 1) == '|')
			{
				free(*buf);
				printerr(": Syntax error \";;\" unexpected\n");
				setsvar("0", "2");
				return (2);
			}
			if (*bufptr == '|')
			{
				free (*buf);
				printerr(": Syntax error \"&\" unexpected\n");
				setsvar("0", "2");
				return (2);
			}
			start = 0;
		}
		if ( bufptr[0] == '\n' && bufptr[1] == 0)
			break;
		if (*bufptr == '#' && !(complete & 3) && (bufptr == *buf || *(bufptr - 1) == ' '))
		{
			*bufptr = 0;
			break;
		}
		complete &= ~4;
#ifdef DEBUGVALID
		printf("!(Complete&3): %d\n", !(complete & 3));
#endif 
		if (*bufptr == '"' && !(complete & 3))
		{
			complete |= 2;
			bufptr++;
			continue;
		}
		if (*bufptr == '"' && complete & 2)
			complete &= ~2;
		if (*bufptr == '\'' && !(complete & 3))
		{
			complete |= 1;
			bufptr++;
			continue;
		}
		if (*bufptr == '\'' && complete & 1)
			complete &= ~1;
		if (bufptr[0] == '&' && !(complete & 3))
		{
			if (bufptr[1] == '&')
			{
				complete |= 4;
				start = 1;
				bufptr++;
			}
			else if (bufptr[1] == '|')
			{
				free(*buf);
				printerr(": syntax error \"|\" unexpected\n");
				setsvar("0", "2");
				return (2);
			}
			else if (bufptr[1] == ';')
			{
				free(*buf);
				printerr(": syntax error \";\" unexpected\n");
				setsvar("0", "2");
				return (2);
			}
		}
		if (bufptr[0] == '|' && !(complete & 3))
		{
			if (bufptr[1] == '|')
			{
				complete |= 4;
				start = 1;
				bufptr++;
			}
			else if (bufptr[1] == ';')
			{
				free(*buf);
				printerr(": syntax error \"|\" unexpected\n");
				setsvar("0", "2");
				return (2);
			}
			else if (bufptr[1] == '&')
			{
				free(*buf);
				printerr(": syntax error \"|\" unexpected\n");
				setsvar("0", "2");
				return (2);
			}
		}
		if (*bufptr == ';')
		{
			if (*(bufptr + 1) == ';')
			{
				free(*buf);
				printerr(": Syntax error \";;\" unexpected\n");
				setsvar("0", "2");
				return (2);
			}
			start = 1;
		}
		bufptr++;
	}
#ifdef DEBUGVALID
	printf("out of while complete: %d\n", complete);
#endif
	if (complete & 7)
	{
#ifdef DEBUGVALID
		printf("not complete: %d\n", complete);
#endif
		bufgl = NULL;
		if (isatty(fd))
		fprintstrs(1, ">", NULL);
		lenr = _getline(&bufgl, fd);
		if (lenr == 0 && !isatty(fd))
		{
			free(buf);
			free(bufgl);
			printerr(": Syntax error: unterminated qouted string\n");
			return (-1);
		}
		if (lenr == -1)
		{
			;
		}
		linebuf = _strlen(*buf);
		newbuf = malloc(linebuf + lenr + 1);
		_strcpy(newbuf, *buf);
		_strcpy(newbuf + linebuf, bufgl);
		free(*buf);
		free(bufgl);
#ifdef DEBUGVALID
		printf("Passing buf: %s\n", newbuf);
#endif
		return (inputvalidator(&newbuf, fd));
	}
#ifdef DEBUGVALID
	printf("Final: %d\n", *buf);
#endif
	sethist(*buf);
	return (parseargs(buf));
}

/*
* shintmode- interactive mode in shell
* Return: 0
*/
int shintmode(void)
{
	char *buflg = NULL, *pwd;
	ssize_t lenr = 0, eoff = 0, ret = 0;
	int istty = isatty(0) && isatty(1);
	while (!eoff)
	{
#ifdef DEBUGMODE
		printf("At terminal primpt\n")
#endif
		if (istty)
		{
			pwd = _getenv("PWD");
			if (pwd != NULL)
			{
				fprintstrs(1, "Homemade shell: ", pwd, "$ ", NULL);
			}
			else
			{
				fprintstrs(1, "Homemade shell$", NULL);
			}
		}
		lenr = _getline(&buflg, STDIN_FILENO);
		if (lenr == 0 || lenr == -1)
		{
			free(buflg);
			break;
		}
		if (buflg[lenr - 1] != '\n')
			eoff = 1;
#ifdef DEBUGMODE
		printf("calling parseargs %s\n", bufgl);
#endif
		ret = inputvalidator(&buflg, STDIN_FILENO);
		buflg = NULL;
		if (eoff)
			break;
	}
	return (ret);
}

/**
* scriptmode- script mode in shell
* @av: arguments
* Return: 0 on success 
*	-1 on failure
*/
int scriptmode(char *av[])
{
	char *bufgl = NULL;
	int infile;
	ssize_t eoff = 0, ret =0, lenr = 0;
	infile = open(av[1], O_RDONLY);
	if (infile == -1)
	{
		fprintstrs(STDERR_FILENO, av[0], ": 0: Can't open", av[1], "\n", NULL);
		return (127);
	}
	while (!eoff)
	{
		lenr = _getline(&bufgl, infile);
		if (lenr == 0 || lenr == -1)
		{
			free(bufgl);
			break;
		}
		if (bufgl[lenr - 1] != '\n')
			eoff = 1;
#ifdef DEBUGMODE
		printf("calling parseargs %s\n", bufgl);
#endif
		ret = inputvalidator(&bufgl, STDIN_FILENO);
		bufgl = NULL;
		if (eoff)
			break;
	}
	close(infile);
	return (ret);
}

/**
* main- runs shell
* @ac: arguments count
* @av: arguments vectors
* @environ: environment matrix
* Return: returns value the last command
*/
int main(int ac, char *av[], char **environ)
{
	int ret = 0;
	char *pptr;
	initsvars(ac - 1, av);
	pptr = _getpid();
	setsvar("$", pptr);
	free(pptr);
	_getline(NULL, -2);
	setallenv(environ, NULL);
#ifdef DEBUGINIT
	printf("?:%s\n", getsvar("?"));
	printf("0:%s\n", getsvar("0"));
	setsvar(strdup("simplevar"), strdup("98"));
	printf("simplevar:%s\n", getsvar("simplevar"));
#endif
	if (ac > 1)
		ret = scriptmode(av);
	else
		ret = shintmode();
	exitcleanup(NULL);
	exit_hist();
	return (ret);
}
