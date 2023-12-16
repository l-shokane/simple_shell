#include "shell.h"

/**
 * bfree - Function that  frees a pointer
 * @ptr: Address of the pointer
 * Return: if pointer is freed 1 or 0 if not.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
