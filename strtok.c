#include<stdio.h>
/*
*
*
*
*
*/
int main(void)
{
	char str[100];
	char strr;
	int i;

	while (str[100])
	{
		for (i = 0;i != '\0'; i++)
		{
			putchar('str[i]');
		}
		str[i++];
	}
	printf("%u", str[i]);
	return (0);
}
