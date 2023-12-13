#include "shell.h"

/**
 *execute_command - function that executes
 * a command in shell
 * @command: command to be executed
 */

char *envp[] = {NULL};

void execute_command(const char *command)
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		my_print("Error in fork process.\n");
		exit(EXIT_FAILURE);
	} else if (child_pid == 0)
	{
		char *args[120];
		int arg_count = 0;

		char *token = strtok((char *)command, " ");

		while (token != NULL)
		{
			args[arg_count++] = token;
			token = strtok(NULL, " ");
		}
		args[arg_count] = NULL;

		execvp(args[0], args);
		
			my_print("Error executing command.\n");
			exit(EXIT_FAILURE);
		
	}
	else
	{
		int status;

		waitpid(child_pid, &status, 0);
	}
}
