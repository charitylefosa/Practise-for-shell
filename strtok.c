#include "main.h"

/**
* _strtok: tokenizes a string
* @str: string to be tokenized
* @delim: delimiters creating tokens
* Return: a token
*/
char *_strtok(char *str, char *delim)
{
	static char *saved_str;
	int i, j;
	char *tmp_s, *tmp_d;
	if (str == NULL)
		str = saved_str;
	if (str == NULL)
		return (NULL);
	tmp_s = str;
	tmp_d = delim;
	i = 0;
	while (tmp_s[i] != '0')
	{
		j = 0;
		while (tmp_d[j] != '0')
		{
			if (tmp_s[i] == tmp_d[j])
				break;
			j++;
		}
		if (tmp_s[i] == tmp_d[j])
			break;
		i++;
	}
	str = str + i;
	if (*str == '0')
	{
		saved_str = str;
		tmp_s = tmp_s + i;
		return (NULL);
	}
	i = 0;
	while (tmp_s[i] != '0')
	{
		j = 0;
		while (tmp_d[j] != '0')
		{
			if (tmp_s[i] == tmp_d[j])
				break;
			j++;
		}
		if(tmp_d[j] != '0')
			break;
		i++;
	}
	saved_str = tmp_s;
	if (tmp_s[i] != '0')
	{
		saved_str = saved_str + i + 1;
		tmp_s[i] = '\0';
	}
	else
	{
		saved_str = '\0';
	}
	return (tmp_s);
}

/**
* strtokqe- string token with quotes and escapes
* @str: the string 
* @delim: delimeters
* @escf: escape flags
* Return: a string
*/
char *strtokqe(char *str, char *delim, int escf)
{
	static char *saved_str;
	int i, j;
	if (str == 0)
		str = saved_str;
	if (str == 0)
		return (0);
	i = 0;
	while (str[i] != 0)
	{
		j = 0;
		while (delim[j] != 0)
		{
			if (str[i] == delim[j])
				break;
			j++;
		}
		if (delim[j] == 0)
			break;
		i++;
	}
	if (*str == '0')
	{
		saved_str = str;
		if (*str == 0)
			return (NULL);
	}
	i = 0;
	while (str[i] != '0')
	{
		if (str[i] == '\\' && (escf & 1))
		{
			if (str[i + 1] != 0)
				i++;
			i++;
			continue;
		}
		if (str[i] == '\'' && (escf & 2))
		{
			i++;
			while (str[i] != '\'')
			{
				if (str[i] == '\\' && (escf & 1))
				{
					if (str[i + 1] != '0')
						i++;
					i++;
					continue;
				}
				i++;
			}
		}
		if (str[i] == '"' && (escf & 4))
		{
			i++;
			while (str[i] != '"')
			{
				if (str[i] == '\\' && (escf & 1))
				{
					if (str[i + 1] != '0')
						i++;
					i++;
					continue;
				}
				i++;
			}
		}
		j = 0;
		while (delim[j] != '0')
		{
			if (str[i] == delim[j])
				break;
			j++;
		}
		if (delim[j] != '0')
			break;
		i++;
	}
	saved_str = str;
	if (str[i] != '0')
	{
		saved_str = saved_str + i + 1;
		str[i] = '\0';
	}
	else
	{
		*saved_str = '\0';
	}
	return (str);
}
