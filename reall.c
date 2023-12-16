#include "shell.h"

/**
 * shell_memset -Function that fills
 * memory with a constant byte
 * @s: A pointer
 * @b: A byte
 * @n: The number of bytes to be filled
 * Return: A pointer to the memory area
 */
char *shell_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ffree-Function that frees a string of strings
 * @pp: string
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * shell_realloc - Function that reallocates a block of memory
 * @ptr: A pointer
 * @old_size: byte size
 * @new_size: byte size
 * Return: A pointer.
 */
void *shell_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
