#include "shell.h"

/**
 * shell_exit - Function that exits the shell
 * @info: A struct parameter
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int shell_exit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = erra_toi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			my_printError(info, "Illegal number: ");
			emy_print(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = erra_toi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * my_cd - Function that changes the current directory of the process
 * @info: A struct parameters
 *  Return: Always 0
 */
int my_cd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		my_print("HERE: >>getcwd failure emsg here<<\n");
	if (!inf->argv[1])
	{
		dir = get_env(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: This should be? */ 
				chdir((dir = get_env(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (str_cmp(info->argv[1], "-") == 0)
	{
		if (!get_env(info, "OLDPWD="))
		{
			my_print(s);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(inf, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: This should be? */
			chdir((dir = get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		my_printError(info, "can't cd to ");
		emy_print(info->argv[1]), _eputchar('\n');
	}
	else
	{
		set_env(info, "OLDPWD", get_env(info, "PWD="));
		set_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * shell_help - Function that changes the current directory of the process
 * @info: A struct parameter
 *  Return: Always 0
 */
int shell_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	my_print("Help call works. Function not yet implemented \n");
	if (0)
		my_print(*arg_array); /* temp att_unused workaround */
	return (0);
}
