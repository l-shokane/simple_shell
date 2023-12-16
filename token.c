#include "shell.h"

/**
 * **split_str - function that splits string into words.
 * @str: string
 * @d: the delimiter string
 * Return: if successful pointer to array OR NULL if it fails
 */

char **split_str(char *str, char *d) 
{
	int i, j, k, m, no_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)

		return (NULL);

	if (!d)
	d = " ";
	for (i = 0; str[i] != '\0'; i++) 
	{
		if (!_delim(str[i], d) && (_delim(str[i + 1], d) || !str[i + 1])) 
		{
			no_words++;
		}
	}
	if (no_words == 0)

	return (NULL);

	s = malloc((1 + no_words) * sizeof(char *));

	if (!s)
	return (NULL);

	for (i = 0, j = 0; j < no_words; j++) 
	{
		while (_delim(str[i], d)) 
		{
		i++;
		}

		k = 0;
	while (!_delim(str[i + k], d) && str[i + k]) 
	{
		k++;
	}
	s[j] = malloc((k + 1) * sizeof(char));
	if (!s[j]) 
	{
	for (k = 0; k < j; k++)
		free(s[k]);
		free(s);
		return (NULL);
	}
	for (m = 0; m < k; m++) 
	{
		s[j][m] = str[i++];
	}
	s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **split_str2 - function that splits string into words
 * @str: string
 * @d: delimiter
 * Return: If successful a pointer to an
 * array OR NULL if it fails
 */
char **split_str2(char *str, char d) 
{
	int i, j, k, m, no_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
	return (NULL);

	for (i = 0; str[i] != '\0'; i++) 
		{
			if ((str[i] != d && str[i + 1] == d) || (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			{
				no_words++;
			}
		}

	if (no_words == 0)
	return (NULL);

	s = malloc((1 + no_words) * sizeof(char *));
	if (!s)
	return (NULL);

	for (i = 0, j = 0; j < no_words; j++)
	{
		while (str[i] == d && str[i] != d)
		{      
			i++;
		}
	k = 0;
	while (str[i + k] != d && str[i + k] && str[i + k] != d)
	{
	k++;
	}
	s[j] = malloc((k + 1) * sizeof(char));
	if (!s[j]) 
	{
	for (k = 0; k < j; k++)
		free(s[k]);
		free(s);
		return (NULL);
	}
	for (m = 0; m < k; m++)
	{
		s[j][m] = str[i++];
	}
	s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
