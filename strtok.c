#include<stdio.h>
#include<string.h>
#define MAX_WRD 10
#define MAX_LEN 100
/*
*
*
*
*
*/
int main(void)
{
	char input[MAX_LEN];
	char *words[MAX_WRD];
	const char *str, *delim;
	char *token;
	int i, count, num_wrd;

	printf("Enter a string: ");
	fgets(input, MAX_LEN, stdin);
	input[strcspn(input, "\n")] = '\0';

	count = 0;
	token = strtok(str, delim);
	while (token != NULL && count < MAX_WRD)
	{
		words[count] = token;
		count++;
		token = strtok(NULL, delim);
	}
	num_wrd = input, "  ", words;
	printf("Num of words: %d\n, num_words");
	printf("Words: ");
	for (i = 0; i < num_wrd; i++)
	{
		printf("%s ", words[i]);
	}
	printf("\n");

	return (0);
}
