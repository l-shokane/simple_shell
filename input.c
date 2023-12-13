#include "shell.h"

/**
 * read_command - fucntion that reads
 * command from user
 * @command: Buffer for command
 * @size: size of buffer
 */

void read_command(char *command, size_t size)
{
	if (fgets(command, size, stdin) == NULL)
	{
		if (feof(stdin))
		{
			my_print("\n");
			exit(EXIT_SUCCESS);
		}
		else {
			my_print("Error reading input. \n");
			exit(EXIT_FAILURE);
		}
	}

	command[strcspn(command, "\n")] = '\0';
}
