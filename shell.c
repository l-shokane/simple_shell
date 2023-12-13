#include "shell.h"

#define MAX_COMMAND_LENGTH 120

/**
 * main - main function
 * Return : 0 always
 */

int main(void)
{
	char command[MAX_COMMAND_LENGTH];

	while (1)
	{
		display_prompt();
		read_command(command, sizeof(command));

		if (strcmp (command, "exit") == 0)
		{
			my_print("Exiting the shell...\n");
			break;
		}

		execute_command(command);
	}
	return (0);
}
