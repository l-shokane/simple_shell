#include "shell.h"

/**
 * input_buf - Function that buffers chained commands
 * @info: A struct parameter
 * @buf: Address of buffer
 * @len: Address
 *
 * Return: bytes that have been read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if the buffer is empty, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = get_line(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* Get rid of trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			rem_comments(*buf);
			make_his_list(info, *buf, info->histcount++);
			/* if (str_char(*buf, ';')) will this be the command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * input_line -  Function that gets a line minus the newline
 * @info: A struct parameter
 *
 * Return: bytes that have been read
 */
ssize_t input_line(info_t *info)
{
	static char *buf; /* this ';'is a command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* There is commands left in the chain buffer */
	{
		j = i; /*The current buf position gets a new init iterator */
		p = buf + i; /* A pointer for return */

		scan_chain(info, buf, &j, i, len);
		while (j < len) /* loops to semicolon or end */
		{
			if (_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; /* increments previous nulled ';'' */
		if (i >= len) /* We have reached the end of buffer? */
		{
			i = len = 0; /* This resets the position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* return pointer to current command position */
		return (str_length(p)); /* length of current command is returned */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from get_line() */
	return (r); /* return length of buffer from get_line() */
}


/**
 * search_buf - Function that reads a buffer
 * @info: A struct parameter
 * @buf: buffer
 * @i: size
 * Return: r
 */
ssize_t search_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * get_line - gets the next line of input from STDIN
 * @info: A struct parameter
 * @ptr: address of pointer to buffer.
 * @length: size of ptr buffer
 *
 * Return: s
 */
int get_line(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = search_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = str_char(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = shell_realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILS! */
		return (p ? free(p), -1 : -1);

	if (s)
		strn_cat(new_p, buf + i, k - i);
	else
		strn_copy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	my_print("\n");
	my_print("simple_shell$ ");
	_putchar(BUF_FLUSH);
}
