#include "main.h"

/**
* parsesetsvar - Parse set shell variables, Return new Buffer
* variable settings
* @buf: Buffer
* Return: String
*/
char *parsesetsvar(char *buf)
{
	char *p, *n, *val, *newbuf, *bufstart = buf;
	int h;
	do {
		h = 0;
		for (p = buf; *p; p++)
		{
#ifdef DEBUGSVARS
			printf("in loop pointer: %s\n", p);
#endif
			if (*p == '=')
			{
				n = _strtok(buf, " ");
				buf = _strtok(NULL, "");
				p = buf;
				h = 1;
				val = _strtok(n, "=");
				val = _strtok(NULL, "");
#ifdef DEBUGSVARS
				printf("In parsesetsvar: setting var %s to %s\n", n, val);
#endif
				setsvar(n, val);
				if (buf == NULL)
				{
					free(bufstart);
					return (NULL);
				}
				continue;
			}
			if (*p == ' ' || *p == 0)
			{
				buf = _strdup(buf);
				free(bufstart);
				return (buf);
			}
			if (p == NULL)
			{
#ifdef DEBUGSVARS
				printf("No other args found, returning\n");
#endif
				free(bufstart);
				return (NULL);
			}
		}
	} while (h && *p != 0);
	newbuf = malloc(sizeof(char) * (_strlen(buf) + 1));
	if (newbuf == NULL)
	{
		free(bufstart);
		return (NULL);
	
	}
	newbuf = _strcpy(newbuf, buf);
	free(bufstart);
	return (newbuf);
}

/**
* subsvars - Substitute in svariables for $names
* @buf: Buffer string that used to be input
* Return: Processed Buffer String
*/
char *subsvars(char **buf)
{
	size_t i, vvlen, vnlen, buflen = _strlen(*buf);
	int inq = 0;
	char *vrp = *buf;
	char *p, *n, *dp, *val, *vlp, *dest;
#ifdef DEBUGSVARS
	printf("In subsvars\n");
#endif
	while (*vrp != 0)
	{
#ifdef DEBUGSVARS
		printf("Top of svar loop buf: %s varpointer: %s\n",*buf, vrp);
#endif
		while (*vrp != '$' && *vrp != 0)
		{
			if (*vrp == '\\')
			{
				vrp++;
				if (*vrp != 0)
					vrp++;
				continue;
			}
			if (inq == 2 && *vrp == '"')
				inq = 0;
			if (inq == 0 && *vrp == '"')
				inq = 2;
			if (*vrp == '\'' && inq != 2)
			{
				vrp++;
				while (*vrp != '\'' && *vrp != 0)
					vrp++;
			}
			vrp++;
			if (*vrp == '$' && (vrp[1] == ' ' || vrp[1] == 0 || vrp[1] == '\n'))
				vrp++;
		}
#ifdef DEBUGSVARS
		printf("At $: %s\n", vrp);
#endif
		dp = vrp;
		if (*vrp == 0)
			return (*buf);
		vrp++;
		for (p = vrp, vnlen = 0; *p != 0 && *p != ' ' && *p != '\n' && *p != '\\'; p++)
			vnlen++;
#ifdef DEBUGSVARS
		printf("varnlen %d varptr %s\n", vnlen, vrp);
#endif
		n = malloc(sizeof(char) * (vnlen + 1));
		if (n == NULL)
			return (NULL);
		for (i = 0; i < vnlen; i++, vrp++)
			n[i] = *vrp;
		n[i] = 0;
#ifdef DEBUGSVARS
		printf("Name: %s\n: varpointer: %s\n",n ,vrp);
#endif
		val = _getenv(n);
		if (val == n)
		{
#ifdef DEBUGSVARS
			printf("%s not env var, checking svars\n", n);
#endif
			val = getsvar(n);
			if (val == n)
				val = _strdup(" ");
		}
		free(n);
#ifdef DEBUGSVARS
		printf("Val got: %s\n", val);
#endif
		vvlen = _strlen(val);
		buflen = buflen - vnlen + vvlen + 1;
#ifdef DEBUGSVARS
		printf("malloc size : %\n",buflen);
#endif
		n = malloc(sizeof(char) * (buflen));
		for (p = *buf, vlp = val, dest = n; *p != 0; p++, dest++)
		{
			if (val != NULL && p == dp)
			{
				while (*vlp != 0)
					*dest++ = *vlp++;
				free(val);
				val = NULL;
				vrp = dest;
				p += vnlen + 1;
				if (*p == 0)
					break;
			}
			*dest = *p;
		}
		*dest = *p;
#ifdef DEBUGSVARS
		printf("Resulting buf is: %s: varpointer %s\n", n, vrp);
#endif
		free(*buf);
		*buf = n;
	}
	return (*buf);
}

/**
* cleanarg - clean escapes and Function quotes
* @arg: arg to clean
* Return: cleaned arguments
*/
char *cleanarg(char *arg)
{
	size_t len = 0;
	int inq = 0;
	char *newbuf, *p, *pp;
	p = arg;
	while (*p != 0)
	{
		if (*p == '\\' && !inq)
		{
			p++;
			if (*p != 0)
			{
				len++;
				p++;
			}
			continue;
		}
		if (*p == '\\' && inq == 2)
		{
			p++;
			if (*p == '$' || *p == '#' || *p == ';' || *p == '\\')
			{
				len++;
				p++;
			}
			else
				len++;
			continue;
		}
		if (!inq && *p == '"')
		{
			inq = 2;
			p++;
			continue;
		}
		if (!inq && *p == '\'')
		{
			inq = 1;
			p++;
			continue;
		}
		if (*p == 0)
			break;
		p++;
		len++;
	}
	newbuf = malloc(sizeof(char) * (len + 1));
	if (newbuf == NULL)
		return (NULL);
	p = arg;
	pp = newbuf;
	inq = 0;
	while (*p != 0)
	{
		if (*p == '\\' && !inq)
		{
			p++;
			if (*p != 0)
				*pp++ = *p++;
			continue;
		}
		if (*p == '\\' && inq == 2)
		{
			p++;
			if (*p == '$' || *p == '#' || *p == ';' || *p == '\\')
				*pp++ = *p++;
			else
				*pp++ = '\\';
			continue;
		}
		if (!inq && *p == '"')
		{
			inq = 2;
			p++;
			continue;
		}
		if (!inq && *p == '\'')
		{
			inq = 1;
			p++;
			continue;
		}
		if ((inq == 1 && *p == '\'') || (inq == 2 && *p == '"'))
		{
			inq = 0;
			p++;
			continue;
		}
		if (*p != 0)
			*pp++ = *p++;
	}
	*pp = 0;
#ifdef DEBUGMODE
	printf("Clean arg return buf %s\n", newptr);
#endif
	free(arg);
	return (newbuf);
}

/**
* tildeexpand - handlers expandings where applicable
* @buf: Buffer to be processed
* Return: buffer that is processed
*/
char *tildeexpand(char *buf)
{
	char *tildeptr = buf;
	char *homepath, *newbuf, *bufptr, *newptr, *endptr;
	int inq = 0;

#ifdef DEBUGMODE
	printf("In tildexpand %s\n", tildeptr);
#endif
	while (*tildeptr != 0)
	{
		tildeptr = buf;
		while (*tildeptr != '~' && *tildeptr != 0)
		{
			if (*tildeptr == '\\')
			{
				tildeptr++;
				if (tildeptr != 0)
					tildeptr++;
				continue;
			}
			if (inq != 1 && *tildeptr == '"')
			{
				inq = 2;
				while (*tildeptr != '"' && *tildeptr != 0)
				{
					if (*tildeptr == '\\')
					{
						tildeptr++;
						inq = *tildeptr != 0 && tildeptr++;
						inq = 2;
						continue;
					}
					tildeptr++;
				}
			}
			if (*tildeptr == '\'' && inq != 2)
			{
				tildeptr++;
				while (*tildeptr != '\'' && *tildeptr != 0)
					tildeptr++;
			}
			tildeptr++;
		}
		if (*tildeptr == 0)
			return (buf);
		endptr = tildeptr;
		while (*endptr != '/' && *endptr != ' ' && *endptr != 0)
			endptr++;
		homepath = _getenv("HOME");
#ifdef DEBUGMODE
		printf("teildeexpand got homepath: %s\n", homepath);
#endif
		if (homepath == NULL)
			return (NULL);
		newbuf = malloc(_strlen(buf) - (size_t)endptr + (size_t) tildeptr + _strlen(homepath) + 1);
		if (newbuf == NULL)
		{
			free(homepath);
			return (NULL);
		}
		bufptr = buf;
		newptr = newbuf;
		while (newptr < tildeptr)
			*newptr++ = *bufptr++;
		bufptr = homepath;
		while (*bufptr)
			*newptr++ = *bufptr++;
		while (*endptr)
			*newptr++ = *endptr++;
		*newptr = 0;
#ifdef DEBUGMODE 
		printf("tilde expanded %s\n", newbuf);
#endif
		free(buf);
		buf = newbuf;
	}
	return (newbuf);
}

/**
* parseargs - Parseargs functions, frees buffer at the ends
* @buf: Buffer pointer
* Return: Return the value of the command
*/
int parseargs(char **buf)
{
	char *av[1024], *ptr, *right, *left;
	int ac, newc, ret = 0;
#ifdef DEBUGMODE
	printf("In parseargs. buf: %s \n", *buf);
#endif
	if (*buf == NULL || **buf == 0)
		return (0);
	ptr = *buf;
	newc = _strlen(*buf) - 1;
	if (ptr[newc] == '\n')
		ptr[newc] = 0;
	if (*buf[0] == 0)
	{
		free(*buf);
		return (0);
	}
#ifdef DEBUGMODE
	printf("Breaking command segments: %p: %s \n", *buf, *buf);
#endif
	left = _strdup(strtokqe(*buf, ";", 7));
	right = _strdup(strtokqe(NULL, "", 7));
	free(*buf);
	*buf = left;
#ifdef DEBUGMODE
	printf("left cmd  %s\n", left);
	printf("right cmd %s\n", right);
#endif
	if (right != NULL && *right != 0)
	{
		parseargs(&left);
		return (parseargs(&right));
	}
#ifdef DEBUGMODE
	printf("Performing logic && %s\n", *buf);
#endif
	left = strtokqe(*buf, "&", 7);
	right = strtokqe(NULL, "", 7);
	if (right != NULL && *right == '&')
	{
		left = _strdup(left);
		right = _strdup(right);
		free(*buf);
		*buf = left;
#ifdef DEBUGMODE
		printf("left cmd  %s\n", left);
		printf("right cmd %s\n", right);
#endif
		ret = parseargs(&left);
		*buf = right;
		right++;
		right = _strdup(right);
		free(*buf);
		if (ret == 0)
			return (parseargs(&right));
		*buf = right;
		strtokqe(right, "|", 7);
		right = strtokqe(NULL, "", 7);
		if (right != NULL)
		{
			right++;
			right = _strdup(right);
			free(*buf);
			return (parseargs(&right));
		}
		free(*buf);
		return (ret);
	}
	else if (right != NULL)
	{
		*(right - 1) = '&';
	}
#ifdef DEBUGMODE
	printf("Performing logic || %s\n", *buf);
#endif
	left = strtokqe(*buf, "|", 7);
	right = strtokqe(NULL, "", 7);
	if (right != NULL && *right == '|')
	{
		left = _strdup(left);
		right = _strdup(right);
		free(*buf);
		*buf = left;
#ifdef DEBUGMODE
		printf("left cmd %s\n", left);
		printf("right cmd %s\n", right);
#endif
		ret = parseargs(&left);
		*buf = right;
		right++;
		right = _strdup(right);
		free(*buf);
		if (ret != 0)
			return (parseargs(&right));
		free(right);
			return (ret);
	}
	else if (right != NULL)
	{
		*(right - 1) = '|';
	}
#ifdef DEBUGMODE
	printf("Subbing vars %s\n", *buf);
#endif
	*buf = subsvars(buf);
	if (*buf == NULL)
		return (-1);
#ifdef DUBUGMODE 
	printf("Expanding tildes %s\n", *buf);
#endif
	*buf = tildeexpand(*buf);
	if (*buf == NULL)
		return (-1);
#ifdef DEBUGMODE 
	printf("Setting vars %s\n", *buf);
#endif
	*buf = parsesetsvar(*buf);
	if (*buf == NULL)
		return (0);
	ac = 0;
	av[ac++] = _strdup(strtokqe(*buf, "\n ", 7));
#ifdef DEBUGMODE
	printf("Got arg %s\n", av[ac - 1]);
#endif
	av[0] = getalias(av[0]);
#ifdef DEBUGMODE
	printf("Alias %s\n", av[0]);
#endif
	if (av[0] != NULL)
		av[0] = cleanarg(av[0]);
#ifdef DEBUGMODE
	printf("Clean args[%d] %s\n",ac - 1, av[ac - 1]);
#endif
	while (av[ac - 1] != NULL)
	{
		av[ac] = _strdup(strtokqe(NULL, "\n", 7));
#ifdef DEBUGMODE
		printf("Got args %s\n", av[ac]);
#endif
		if (av[ac] != NULL)
			av[ac] = cleanarg(av[ac]);
#ifdef DEBUGMODE
		printf("Clean arg %s\n", av[ac]);
#endif
		ac++;
	}
#ifdef DEBUGMODE
	printf("After cleaning\n");
#endif
	ac--;
	av[ac] = NULL;
	free(*buf);
	*buf = NULL;
	ret = builtincall(av);
#ifdef DEBUGMODE
	printf("After command call ret %d\n", ret);
#endif
#ifdef DEBUGMODE
	printf("Free av strings\n");
#endif
	for (ac = 0; av[ac] != NULL; ac++)
		free(av[ac]);
#ifdef DEBUGMODE
	printf("Returning ret %dn", ret);
#endif
	return (ret);
}
