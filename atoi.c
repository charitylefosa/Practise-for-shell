#include "main.h"

/**
* _atoi- converts a string to an int
* @s: string to be converted
* Return: converted int
*/
int _atoi(char *s)
{
	int i, neg, check_num;
	unsigned int x, sum;

	neg = 0;
	check_num = 0;
	sum = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if ((s[i] > '9' || s[i] < '0') && check_num > 0)
			break;
		if (s[i] == '-')
			neg++;
		if (s[i] >= '0' && s[i] <= '9')
			check_num++;
		i++;
	}
	i = i - 1;
	x = 1;
	while (check_num > 0)
	{
		sum = sum + ((s[i] - '0') * x);
		x = x *10;
		i--;
		check_num--;
	}
	if (neg % 2 != 0)
		sum = sum * -1;
	return (sum);
}

/**
* _putchar- writes the character c to STDOUT
* @c: character to print
* Return: on success 1
*	-1 on error
*/
int _putchar(char s)
{
	return (write(1, &s, 1));
}

/**
* printenv- to print environment
* Return: 0 on success
*/
int _printenv(void)
{
	/* getenviron() - static wrapper copy of whole environ */
	char ** environ = *(getenviron());
	int i, j;

	i = 0;
	while (environ[i])
	{
	j = 0;
	while (environ[i][j] != 0)
	{
		_putchar(environ[i][j]);
		j++;
	}
	_putchar('\n');
	i++;
	}
	return (0);
}
