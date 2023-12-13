#include "shell.h"

/**
 * my_print - custom print function
 * @message: pointer
 */

void my_print(const char *message)
{
	write(STDOUT_FILENO, message, strlen(message));
}
