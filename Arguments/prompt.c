#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
/*
*
*
*
*/
int main(void)
{
	char *ptr;
	size_t len;
	ssize_t read;

	putchar('$');
	putchar('\n');
	read = getline(&ptr, &len, stdin);
	putchar(read);
	free(ptr);
	return (0);
}
