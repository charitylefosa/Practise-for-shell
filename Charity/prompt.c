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
	putchar(' ');
	read = getline(&ptr, &len, stdin);
	putchar(read);
	if (read != '\0')
	{
		printf("%s", ptr);
	}
	else
		printf("Error");
	free(ptr);
	return (0);
}
