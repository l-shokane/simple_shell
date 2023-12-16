#include "shell.h"

/**
 * str_length -  Function that returns the length of a string
 * @s: the string
 * Return: length of string as integer
 */
int str_length(char *s)
{
	int i = 0;

	if (s == NULL)
	{
		return (0);
	}

	while (*s != '\0')
	{
		i++;
		s++;
	}

	return (i);
}

/**
 * str_cmp - Function that compares two strings.
 * @s1: string 1
 * @s2: string 2
 * Return: 0 is s1 is the same as s2 OR
 * 	negative is s1 less than s2 OR
 * 	positive is s1 is greater than s2.
 */
int str_cmp(char *s1, char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
		{
			if (*s1 != *s2)
			{
				return (*s1 - *s2);
			}
		s1++;
		s2++;
		}

	if (*s1 == *s2)
	{
		return (0);
	}
	else
	{
		return (*s1 < *s2 ? -1 : 1);
	}
}


/**
 * _startswith - Function that checks if shell starts with command
 * @shell: string 
 * @command: the substring to find
 * Return: Address of next char of shell OR NULL
 */
char *_startswith(const char *shell, const char *command)
{
	while (*shell != '\0')
		{
			if (*command != *shell)
			{
				return (NULL);
			}
		command++;
		shell++;
		}

	return (char *)shell;
}

/**
 * str_cnct - Function that concatenates two strings
 * @dest: The destination buffer
 * @src: The source buffer
 *
 * Return: A pointer to destination buffer
 */
char *str_cnct(char *dest, char *src)
{
	char *ret = dest;

	while (*dest != '\0')
		{
			dest++;
		}

	while (*src != '\0')
	{
		*dest++ = *src++;
	}

	*dest = *src;

	return (ret);
}

