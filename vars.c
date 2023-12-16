#include "shell.h"

/**
 * _chain- Function that checks if buffer is a chain delimiter
 * @info: A struct parameter
 * @buf: A buffer char
 * @p: Address
 * Return: If buf is chain delim 1 OR 0 if not.
 */
int _chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * scan_chain - function that checks if we continue chaining
 * @info: A struct parameter
 * @buf: A buffer char
 * @p: Address
 * @i: first element in buf
 * @len: buffer length
 * Return: void
 */
void scan_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * change_alias - Function that replaces an aliases in string token
 * @info: A struct parameter
 * Return: if it succeeds 1 OR 0 if it fails
 */

int change_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_begins_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = str_char(node->str, '=');
		if (!p)
			return (0);
		p = strd_up(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * change_vars - function for replacing vars in tokenized string
 * @info: A struct parameter
 * Return: if it succeeds 1 OR 0 if it fails
 */
int change_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!str_cmp(info->argv[i], "$?"))
		{
			change_string(&(info->argv[i]),
				strd_up(convrt_num(info->status, 10, 0)));
			continue;
		}
		if (!str_cmp(info->argv[i], "$$"))
		{
			change_string(&(info->argv[i]),
				strd_up(convrt_num(getpid(), 10, 0)));
			continue;
		}
		node = node_begins_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			change_string(&(info->argv[i]),
				strd_up(str_char(node->str, '=') + 1));
			continue;
		}
		change_string(&info->argv[i], strd_up(""));

	}
	return (0);
}

/**
 * change_string - Function that replaces a string
 * @old: old string
 * @new: new string
 * Return: if it succeeds 1 OR 0 if not
 */
int change_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
