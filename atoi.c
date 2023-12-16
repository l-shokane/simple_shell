#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @inf: A struct parameter
 * Return: if successful 1 or 0 if not.
 */
int interactive(inf_t *inf)
{
	return (isatty(STDIN_FILENO) && inf->readfd <= 2);
}

/**
 * _delim - Function that checks if character is a delimiter
 * @c: character
 * @delim: delimiter string
 * Return: if successful 1 OR 0 if not.
 */
int _delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *is_alpha - Function that checks for alphabetic character
 *@c:  character 
 *Return: 1 if c is alphabetic OR 0 otherwise
 */

int is_alpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *shell_atoi - Function converts a string to an integer
 *@s: the string 
 *Return: if successful 0 0R -1 if not.
 */

int shell_atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
