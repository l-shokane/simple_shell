#include "shell.h"

/**
 * str_length -  Function that returns the length of a string
 * @s: the string
 * Return: length of string as integer
 */
int str_length(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * str_cmp - Function that compares two strings.
 * @s1: string 1
 * @s2: string 2
 * Return: 0 is s1 is the same as s2 OR
 * negative is s1 less than s2 OR
 * positive is s1 is greater than s2.
 */
int str_cmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}


/**
 * begins_with- Function that checks if shell starts with command
 * @haystack: string
 * @needle: the substring to find
 * Return: Address of next char of shell OR NULL
 */
char *begins_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * str_cat - Function that concatenates two strings
 * @dest: The destination buffer
 * @src: The source buffer
 *
 * Return: A pointer to destination buffer
 */
char *str_cat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

