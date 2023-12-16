#include "shell.h"

/**
 * get_environ - Function that returns the string array copy of environ
 * @info: A struct parameter
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_swapped)
	{
		info->environ = string_list(info->env);
		info->env_swapped = 0;
	}

	return (info->environ);
}

/**
 * unset_env -Function that removes an environment variable
 * @info: A Struct parameter
 *  Return: if successful 1 or 0 if not.
 * @var: the string
 */
int unset_env(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = begins_with(node->str, var);
		if (p && *p == '=')
		{
			info->env_swapped = node_del_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_swapped);
}

/**
 * set_env - Function that Initialize a new environment variable
 * @info:  A struct parameter
 * @var: the string
 * @value: the string var value
 *  Return: Always 0
 */
int set_env(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(str_length(var) + str_length(value) + 2);
	if (!buf)
		return (1);
	copy_str(buf, var);
	str_cat(buf, "=");
	str_cat(buf, value);
	node = info->env;
	while (node)
	{
		p = begins_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_swapped = 1;
			return (0);
		}
		node = node->next;
	}
	add_end_node(&(info->env), buf, 0);
	free(buf);
	info->env_swapped = 1;
	return (0);
}
