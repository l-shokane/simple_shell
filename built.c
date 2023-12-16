#include "shell.h"

/**
 * shell_history - Function that displays the history list.
 * @info: A struct parameter
 *  Return: Always 0
 */
int shell_history(info_t *info)
{
	my_printList(info->history);
	return (0);
}

/**
 * unset_alias - Function that sets alias to string
 * @info: A struct parameter
 * @str: the string
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = str_char(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = node_del_index(&(info->alias),
		get_index_node(info->alias,
			node_begins_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - Function that sets alias to string
 * @info: A struct parameter
 * @str: the string
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = str_char(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_end_node(&(info->alias), str, 0) == NULL);
}

/**
 * _printalias - Function that prints an alias string
 * @node: node
 * Return: Always 0 on success, 1 on error
 */
int _printalias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = str_char(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		my_print(p + 1);
		my_print("'\n");
		return (0);
	}
	return (1);
}

/**
 * shell_alias - Function that mimics the alias builtin
 * @info: A struct parameter
 *  Return: Always 0
 */

int shell_alias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			_printalias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = str_char(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			_printalias(node_begins_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
