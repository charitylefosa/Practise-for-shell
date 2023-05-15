#include<stdio.h>
#include<stdlib.h>
/**
*
*
*
*
*/
int main(__attribute__((__unused__))int ac, char **av)
{
	av++; /* to skip the first element which is the program name */

	while (*av != NULL)
	{
		printf("%s\n", *av);
		av++;
	}
	return (0);
}
