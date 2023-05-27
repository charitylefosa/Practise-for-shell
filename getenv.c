#include "main.h"
#include <stdlib.h>
#include <string.h>

/**
 * getallenv - getting all of environment
 *
 * Return: Env
 *
*/
char **getallenv()
{
	char **environ = *(getenviron());
	char **envcopy;
	size_t len = 0;

	envcopy = environ;
	while (envcopy[len] != NULL)
		len++;
#ifdef DEBUGMODE
	printf("Got length of env lines %zu\n , coping now\n", len);
#endif
	envcopy = malloc(sizeof(char **) * (len + 1));
	if (envcopy == NULL)
		return (NULL);
	while (len > 0)
	{
		envcopy[len] = environ[len];
		len--;
	}
	envcopy[len] = environ[len];
		return (envcopy);
}

/**
 * setallenv - Whole envi to be set for new value
 * @envin: Environment
 * @newval: New values to be added
 * Return: if fail is -1, is success is 0
*/
int setallenv(char **envin, char *newval)
{
	char ***environ = getenviron();
	size_t len = 0;
#ifdef DEBUGMODE
	if (newval != NULL)
		printf("In satallenv, neval: %s\n", newval);
#endif
	while (envin[len] != NULL)
		len++;
	if (newval != NULL)
		len++;
	*environ = malloc(sizeof(char **) * (len + 1));
	if (*environ == NULL)
		return (-1);
	for (len = 0; envin[len] != NULL; len++)
		if (newval == NULL)
		{
			(*environ)[len] = _strdup(envin[len]);
		}
		else
			(*environ)[len] = envin[len];
	if (newval != NULL)
	{
#ifdef DEBUGMODE
		printf("Adding newval: %s\n", newval);
#endif
		(*environ)[len] = newval;
		len++;
	}
	(*environ)[len] = NULL;
#ifdef DEBUGMODE
	printf("End. Free old environ if adding a string\n");
#endif
	if (newval != NULL)
		free(envin);
	return (0);
}


char *_getenv(char *n)
{
	char **environ = *(getenviron());
	int i, j;
	char *s;

#ifdef DEBUGMODE
	printf("In getenv: %s\n", n);
#endif

	i = 0;
	while (environ[i] != NULL)
	{
		s = environ[i];
		j = 0;
#ifdef DEBUGMODE
		printf("Checking against %s\n", environ[i]);
#endif
		while (s[j] == n[j])
		{
			j++;
			if (n[j] == 0 && s[j] == '-')
				return (_strdup(s + j + 1));
		}
		i++;
	}
	return (n);
}

/**
 * _setenv - Get Environment for a value
 * @name: Name variables
 * @val: value or Var
 * Return: 0 or Setallenv when success, -1 when fail
 */
 
int _setenv(char *n, char *val)
{
	char ***environrt = getenviron();
	char **environ = *environrt;
	int i, j, name, vall;
	char *s, *r;
#ifdef DEBUGMODE
	printf("In setenv: %s\nof value %s\n", n, val);
#endif
	if (n == NULL || val == NULL)
		return (0);
	name = _strlen(n);
	vall = _strlen(val);
	r = malloc(sizeof(char) * (name + vall + 2));
	if (r == NULL)
		return (-1);
	s = r;
	_strcpy(s, n);
	s+= name;
	_strcpy(s++, "=");
	_strcpy(s, val);
	s += vall;
	*s = 0;
#ifdef DEBUGMODE
	printf("R mallocd %s\n", r);
#endif
	i = 0;
	while (environ[i] != NULL)
	{
		s = environ[i];
		j = 0;
		while (s[j] == n[j])
		{
			j++;
			if (n[j] == 0 && s[j] == '=')
			{
				free(environ[i]);
				environ[i] =r;
				return(0);
			}
		}
		i++;
	}
	return(setallenv(*environrt, r));
}

/**
 * _unsetenv - unset Envir
 * @name: name of var to unset
 * Return: 0 on successes
*/
int _unsetenv(char *n)
{
	char **environ = *getenviron();
	int i, j, check = 0;
	char *s;
	char **env;
#ifdef DEBUGMODE
	printf("In unsetenv: %s\n", n);
#endif
	if (n == NULL)
		return (0);
	i = 0;
	while (environ[i] != NULL)
	{
		s = environ[i];
		j = 0;
		while (s[j] == n[j])
		{
			j++;
			if (s[j] == '=' && n[j] == '\0')
			{
				check = 1;
				break;
			}
		}
		if (check == 1)
			break;
		i++;
	}
	free(environ[i]);
	while (environ[i] != NULL)
	{
		environ[i] = environ[i + 1];
		i++;
	}
	environ[i] = NULL;
	env = environ;
	setallenv(env, "");
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
	return (0);
}
