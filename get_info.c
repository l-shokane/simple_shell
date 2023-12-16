#include "shell.h"

/**
 * init_inf - Function that initializes inf_t struct
 * @info: A struct parameter
 */
void init_inf(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * put_inf - Function that initializes inf_t struct
 * @info: A struct parameter
 * @av: argument vector
 */
void put_inf(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = strd_up(inf->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		change_alias(info);
		change_vars(info);
	}
}

/**
 * rem_inf - Function that frees inf_t struct fields
 * @info:  A struct parameter
 * @all: True 
 */
void rem_inf(info_t *info, int all)
{
	free_str(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			node_list_free(&(info->env));
		if (info->history)
			node_list_free(&(info->history));
		if (info->alias)
			node_list_free(&(info->alias));
		free_str(info->environ);
		inf->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (inf->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

