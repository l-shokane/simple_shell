#include "shell.h"

/**
 * main - main function
 * @ac: argument count
 * @av: argument vector
 * Return: if successful 0 or 0 if not.
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				emy_print(av[0]);
				emy_print(": 0: Can't open ");
				emy_print(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
	}
	pop_list_env(info);
	scan_his(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
