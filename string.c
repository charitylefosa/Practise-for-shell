#include "main.h"

/**
* _strcmp- compares two strings 
* @s1: string 1
* @s2: string 2
* Return: +int or -int or 0 
*/
int _strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (-1);
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			return (s1[i] - s2[i]);
		}
		i++;
	}
	return (s1[i] - s2[i]);
}

/**
* _strlen- counts string length 
* @str: the string 
* Return: string length
*/
size_t _strlen(char *str)
{
	size_t length = 0;

	while (*str++)
		length++;

	return (length);
}

/**
* _strcpy - copies strings
* @dest: string 1
* @scr: string 2
* Return: string
*/
char *_strcpy(char *dest, char *src)
{
	char *ptr = dest;

	while (*src)
		*ptr++ = *src++;
	*ptr = *src;

	return (dest);
}
/**
* _strdup- concat strings 
* @str: string
* Return: string
*/
char *_strdup(char *str)
{
	char *new;

	if (str == NULL)
		return (NULL);
	new = malloc(sizeof(char) * (_strlen(str) + 1));
	if (new == NULL)
		return (NULL);
	_strcpy(new, str);
	return (new);
}

/**
*_strcat- concnat strings  
* @dest: string 1
* @src: string 2
* Return: string
*/
char *_strcat(char *dest, char *src)
{
	char *ptrs = dest;

	while (*ptrs)
		ptrs++;
	while (*src)
		*ptrs++ = *src++;
	*ptrs = 0;
	return (dest);
}
