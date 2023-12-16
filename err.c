#include "shell.h"

/**
 * erra_toi - Function that converts a string to an integer
 * @s: the string
 * Return: if successful 0 or -1 if it fails.
 */
int erra_toi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * my_printError - Function that prints an error message
 * @info: A struct parameter
 * @estr: string 
 * Return: if successful 0 or -1 if Fails.
 */
void my_printError(info_t *info, char *estr)
{
	emy_print(info->fname);
	emy_print(": ");
	dec_print(info->line_count, STDERR_FILENO);
	emy_print(": ");
	emy_print(info->argv[0]);
	emy_print(": ");
	emy_print(estr);
}

/**
 * dec_print - Function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the file descriptor to write to
 * Return: number of characters printed
 */
int dec_print(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convrt_num - Function that converts, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: string
 */
char *convrt_num(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * rem_comments - function replaces first instance of '#' with '\0'
 * @buf: address
 * Return: Always 0;
 */
void rem_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
