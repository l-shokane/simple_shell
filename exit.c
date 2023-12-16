#include "shell.h"

/**
 **string_copy -  Function that copies a string
 *@dest: the destination string 
 *@src: the source string
 *@n: the number of characters
 *Return: the concatenated string
 */
char *string_copy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **strn_cat - Function that concatenates two strings
 *@dest: the destination string
 *@src: the source string
 *@n: the number of bytes to be used
 *Return: The concatenated string
 */
char *strn_cat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 **str_char - Function that locates a character in a string
 *@s: the string
 *@c: the character
 *Return: (s) a pointer to the memory
 */
char *str_char(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
