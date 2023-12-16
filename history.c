#include "shell.h"

/**
 * get_his_file -Function that gets the history file
 * @info: A struct parameter
 * Return: allocated string that has history file
 */

char *get_his_file(info_t *info)
{
	char *buf, *dir;

	dir = get_env(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (str_length(dir) + str_length(HISTORY_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	copy_str(buf, dir);
	str_cnct(buf, "/");
	str_cnct(buf, HISTORY_FILE);
	return (buf);
}

/**
 * write_his -  Function that creates a file.
 * @info: A struct parameter
 *
 * Return: if successful 1 or -1 if not.
 */
int write_hist(info_t *info)
{
	ssize_t fd;
	char *filename = get_his_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		my_printfd(node->str, fd);
		my_printfd('\n', fd);
	}
	my_printfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * scan_his - Function reads history from file
 * @info: A struct parameter
 *
 * Return: if successful history count 0R 0 if not
 */
int scan_his(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_his_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
		buf[i] = 0;
		make_his_list(info, buf + last, linecount++);
		last = i + 1;
		}
	if (last != i)
		make_his_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		node_del_index(&(info->history), 0);
	new_numHis(info);
	return (info->histcount);
}

/**
 * make_his_list - Function that adds entry to history linked list
 * @info: A struct parameter
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int make_his_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_end_node(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * new_numHis - Function that renumbers the history linked list after changes
 * @info: A struct parameter
 *
 * Return: the new histcount
 */
int new_numHis(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
