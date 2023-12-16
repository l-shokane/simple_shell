#include "shell.h"

/**
 * shell_env - Function that prints the current environment
 * @info: A Struct parameter
 * Return: Always 0
 */
int shell_env(info_t *info)
{
	myprint_listStr(info->env);
	return (0);
}

/**
 * get_env - Function that gets the value of an environ variable
 * @info: A struct parameter
 * @name: environment var name
 * Return: the value
 */
char *get_env(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = begins_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * shell_setenv - Function that Initializes a new environment variable.
 * @info: A struct parameter
 *  Return: Always 0
 */
int shell_setenv(info_t *info)
{
	if (info->argc != 3)
	{
		emy_print("Incorrect number of arguments\n");
		return (1);
	}
	if (set_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * shell_unsetenv -  Function that removes an environment variable
 * @info: A struct parameter
 *  Return: Always 0
 */
int shell_unsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		emy_print("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unset_env(info, info->argv[i]);

	return (0);
}

/**
 * pop_list_env - Function that populates env linked list
 * @info: A struct parameter
 * Return: Always 0
 */
int pop_list_env(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_end_node(&node, environ[i], 0);
	info->env = node;
	return (0);
}
