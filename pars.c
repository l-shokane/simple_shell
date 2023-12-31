#include "shell.h"

/**
 *_cmd - Function that determines if
 * a file is an executable command
 * @info: A struct parameter
 * @path: A path for the file
 * Return: if successful 1 OR 0 if not
 */

int _cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars -  Function that duplicates characters
 * @pathstr: PATH string
 * @start: starting index
 * @stop: stopping index
 * Return: A pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * disc_path - Function that finds the cmd in the PATH string
 * @info: A struct parameter
 * @pathstr: PATH string
 * @cmd: The cmd to discover in PATH
 * Return: if successful the full path of cmd OR NULL
 */
char *disc_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((str_length(cmd) > 2) && begins_with(cmd, "./"))
	{
		if (_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				str_cat(path, cmd);
			else
			{
				str_cat(path, "/");
				str_cat(path, cmd);
			}
			if (_cmd(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
