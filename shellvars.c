#include "main.h"

/**
* initsvars- initialize vars
* @ac: argument count
* @av: argument vector
* Return: count
*/
int initsvars(int ac, char **av)
{
	ShellVar **specialroot = getspecial();
	ShellVar *special;
	ShellVar *ptr;
	int i = 0;
	char nums[2] = {0, 0};

	*specialroot = malloc(sizeof(ShellVar) * 15);
	if (*specialroot == NULL)
		return (-1);
	special = *specialroot;
#ifdef DEBUGMODE
	printf("special:%p:*getspecial():%p:\n", *(getspecial()), *(getspecial()));
#endif
	special->val = _strdup("0");
	special->n = _strdup("?");
	ptr = special + 1;
	special->next = ptr;
	while (av[i] != NULL)
	{
#ifdef DEBUGMODE
		print("av[%d]=%s\n", i, av[i]);
#endif
		nums[0] = i + '0';
		ptr->val = _strdup(av[i]);
		ptr->n = _strdup(nums);
		ptr->next = ptr + 1;
		ptr = ptr->next;
		i++;
	}
	while (i < 10)
	{
		nums[0] = i + '0';
		ptr->val = _strdup("0");
		ptr->n = _strdup(nums);
		ptr->next = ptr + 1;
		ptr = ptr->next;
		i++;
	}
	ptr->n = _strdup("$");
	ptr->val = _strdup("0");
	ptr->next = ptr + 1;
	ptr = ptr->next;
	ptr->n = itos(ac);
	ptr->next = NULL;
	return (0);
}

/**
* getsvar- gets variable in shell 
* @n: name of the variable
* Return: the name or argument if name found
*/
char *getsvar(char *n)
{
	ShellVar *special = *(getspecial()), *vars = *(getvars());
	ShellVar *ptr = special;

	while (ptr != NULL && _strcmp(ptr->n, n))
	{
#ifdef DEBUGMORE
		printf("Checked .%s. against .%s.\n", n, ptr->n);
#endif
		ptr = ptr->next;
	}
	if (ptr != NULL)
	{
#ifdef DEBUGMODE
		printf("Returning special var %s:%s\n", ptr->n, ptr->val);
#endif
		return (_strdup(ptr->val));
	}
	ptr = vars;
	while (ptr != NULL && _strcmp(ptr->n, n))
	{
#ifdef DEBUGMODE
		printf("Checked .%s. agaist .%s.\n", n, ptr->n);
#endif
		ptr = ptr->next;
	}
	if (ptr == NULL)
	{
#ifdef DEBUGMODE
		printf("Var not found %s\n", n);
#endif
		return (n);
	}
#ifdef DEBUGMODE
	printf("Returning var %s\n", ptr->val);
#endif
	return (_strdup(ptr->val));
}

/**
* setsvar- sets shell var 
* @n: name of shell var
* @val: value of shell var
* Return: 0 on success
*/
int setsvar(char *n, char *val)
{
	ShellVar **vars = getvars();
	ShellVar *special = *(getspecial());
	ShellVar *ptr = special, *new;

#ifdef DEBUGMODE
	printf("in setvar, special address: %p\n", special);
	printf("Got %s %s\n", n, val);
#endif
	while (_strcmp(ptr->n, n) && ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	if (!_strcmp(ptr->n, n))
	{
#ifdef DEBUGMODE
		printf("Setting special %s to %s\n", ptr->n, val);
		printf("ptr -> val %p\n", ptr->val);
#endif
		free(ptr->val);
		ptr->val = _strdup(val);
		return (0);
	}
	ptr = *vars;
#ifdef DEBUGMODE
	printf("vars address %p\n", *vars);
#endif
	if (ptr == NULL)
	{
#ifdef DEBUGMODE
		printf("Setting new $s to %s\n", n, val);
#endif
		new = malloc(sizeof(new));
		if (new == NULL)
			return (-1);
		new->n = _strdup(n);
		new->val = _strdup(val);
		new->next =  NULL;
		return (0);
	}
	while (_strcmp(ptr->n, n) && ptr->next != NULL)
		ptr = ptr->next;
	if (ptr != NULL && !_strcmp(ptr->n, n))
	{
#ifdef DEBUGMODE
		printf("Setting %s to %s\n", ptr->n, val);
#endif
		free(ptr->val);
		ptr->val = _strdup(val);
	}
	else
	{
#ifdef DEBUGMODE
		printf("Setting new %s to %s\n", n, val);
#endif
		new = malloc(sizeof(ShellVar));
		if (new == NULL)
			return (-1);
		new->n = _strdup(n);
		new->val = _strdup(val);
		new->next = NULL;
		ptr->next = new;
	}
	return (0);
}

/**
* unsetsvar- unsets shell var
* @n: name of shell var
* Return: 0 on success
*/
int unsetsvar(char *n)
{
	ShellVar *vars = *getvars();
	ShellVar *ptr = vars;
	ShellVar *next;
#ifdef DEBUGMODE
	printf("In unsetsvar:vars:%p:name:%s\n", vars, n);
#endif
	if (vars == NULL)
		return (0);
#ifdef DEBUGMODE
	printf("ptr->name: %s\n", ptr->n);
#endif
	if (!_strcmp(ptr->n, n))
	{
#ifdef DEBUGMODE
		printf("First node match\n");
#endif
		*vars = *vars->next;
		free(ptr->n);
		free(ptr->val);
		free(ptr);
		return (0);
	}
	while (ptr->next != NULL && strcmp(ptr->n, n))
		ptr = ptr->next;
	if (!strcmp(ptr->next->n, n))
	{
		next = ptr->next->next;
		free(ptr->next->n);
		free(ptr->next->val);
		free(ptr->next);
		ptr->next = next;
	}
	return (0);
}
