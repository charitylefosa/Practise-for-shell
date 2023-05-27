#include "main.h"

ShellVar **getspecial();
ShellVar **getvars();
AliasData **getalist();

char ***getenviron()
{
	static char **environ;
	return (&environ);
}

/**
 * exitcleanup - various vars are cleaned before exit
 * @av: arg list to be freed (if any)
 * Return: void
 */
void exitcleanup(char **av)
{
	ShellVar *ptr = *(getspecial()), *snext;
	AliasData *t = *(getalist()), *anext;
	char **environ = *(getenviron());
	int i;
	i = 0;
	if (av != NULL)
		for (i = 0; av[i] != NULL; i++)
			free(av[i]);
	i = 0;
	while (environ[i] != NULL)
		free(environ[i++]);
	free(environ);
	while (ptr != NULL)
	{
		free(ptr->val);
		free(ptr->n);
		ptr = ptr->next;
	}
	free(*(getspecial()));
	ptr = *(getvars());
	while (ptr != NULL)
	{
		free(ptr->val);
		free(ptr->n);
		snext = ptr->next;
		free(ptr);
		ptr = snext;
	}
	while (t != NULL)
	{
		free(t->val);
		free(t->n);
		anext = t->next;
		free(t);
		t = anext;
	}
}
