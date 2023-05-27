#include "main.h"

/**
* gethistory- gets the history list
* Return: 0 on success
*/
HistList **gethistory()
{
	static HistList *hlist;
	return (&hlist);
}

/**
* sethist- sets history list
* @cmd: command
* Return: 0 on success
*/
int sethist(char *cmd)
{
	HistList **hlistrt = gethistory();
	HistList *hlist = *hlistrt;
	HistList *ptr = hlist;
	HistList *new;

	if (hlist == NULL)
	{
		new = malloc(sizeof(HistList));
		if (new == NULL)
			return (-1);
		new->cmd = _strdup(cmd);
		new->next = NULL;
		*hlistrt = new;
		return (0);
	}
	while (ptr->next != NULL)
		ptr = ptr->next;
	new = malloc(sizeof(HistList));
	if (new == NULL)
		return (-1);
	new->cmd = _strdup(cmd);
	new->next = NULL;
	ptr->next = new;
	return (0);
}

/**
* print_hist- prints al listint elements
* Return: number of elements
*/
int print_hist(void)
{
	HistList **hlistrt = gethistory();
	HistList *h = *hlistrt;
	int i, len, numlen;
	char *s, *num;

	i = 0;
	while (h != NULL)
	{
		len = _strlen(h->cmd);
		s =h->cmd;
		num = itos(i);
		numlen = _strlen(num);
		write(1, num, numlen);
		putchar(' ');
		write(1, s, len);
		h = h->next;
		i++;
	}
	return (i);
}

/**
* exit_hist- exits the history and copies to file
* Return: an int
*/
int exit_hist(void)
{
	int fd;
	char *file = ".simples_shell_history";
	int len;
	char *s;

	HistList **hlistrt = gethistory();
	HistList *hlist = *hlistrt;
	HistList *ptr = hlist;

	fd = open(file, O_CREAT | O_RDWR, 0600);
	if (fd == -1)
		return (-1);
	while (hlist != NULL)
	{
		ptr = hlist->next;
		s = hlist->cmd;
		len = _strlen(s);
		write(fd, s, len);
		free(hlist->cmd);
		free(hlist);
		hlist = ptr;
	}
	close(fd);
	return (1);
}
