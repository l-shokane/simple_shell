#include "shell.h"

/**
 * hsh - shell loop
 * @info: A struct parameter
 * @av: argument vector
 * Return: If successful 0 OR 1
 */
int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		init_info(info);
		if (interactive(info))
			my_print("simple_shell$ ");
		_eputchar(BUF_FLUSH);
		r = input_line(info);
		if (r != -1)
		{
			put_info(info, av);
			builtin_ret = disc_builtin(info);
			if (builtin_ret == -1)
				disc_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		rem_info(info, 0);
	}
	write_his(info);
	rem_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * disc_builtin - function that finds a builtin command
 * @info: A struct parameter
 * Return: if builtin not found -1
 *          if successful 0
 *          if builtin found but failed 1
 *          if builtin calls exit() -2
 */
int disc_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", shell_exit},
		{"env", shell_env},
		{"help", shell_help},
		{"history", shell_history},
		{"setenv", shell_setenv},
		{"unsetenv", shell_unsetenv},
		{"cd", shell_cd},
		{"alias", shell_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (str_cmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * disc_cmd - Function that finds a command in PATH
 * @info: A struct parameter
 */
void disc_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = disc_path(info, get_env(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		exec_fork(info);
	}
	else
	{
		if ((interactive(info) || get_env(info, "PATH=")
			|| info->argv[0][0] == '/') && _cmd(info, info->argv[0]))
			exec_fork(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			my_printError(info, "not found\n");
		}
	}
}

/**
 * exec_fork - Function that forks an exec thread to run cmd
 * @info: A struct parameter
 */
void exec_fork(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* HERE: MUST PLACE AN ERROR FUNC */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			rem_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* HERE: MUST INSERT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				my_printError(info, "Permission denied\n");
		}
	}
}
