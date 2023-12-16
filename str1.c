#include "shell.h"

/**
 * copy_str - Function that copies a string
 * @dest: destination
 * @src: source
 *
 * Return:  A pointer to destination
 */
char *copy_str(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
	{
		return (dest);
	}

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * strd_up - Function that duplicates a string
 * @str:string
 * Return: A pointer to the duplicated string
 */
char *strd_up(const char *str)
{
	int length = 0;
	char *les;

	if (str == NULL)
	{
		return (NULL);
	}

	while (*str++)
	{
		length++;
	}

	ret = malloc(sizeof(char) * (length + 1));
	if (!les)
	{
		return (NULL);
	}

	for (length++; length--;)
	{
		ret[length] = *--str;
	}

	return (les);
}

/**
 * my_print -Function that prints an input string
 * @str: string
 */
void my_print(char *str)
{
	int i = 0;

	if (!str)
	{
		return;
	}

	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - function that writes the character c to stdout
 * @c: character
 * Return: if successful 1
 * On error, -1 is returned.
 */
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
	{
		buf[i++] = c;
	}

	return (1);
}
