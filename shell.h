#ifndef SHELL_H
#define SHELL_H

/* LIBRARIES */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

/*Function prototypes */

void display_prompt(void);
void my_print(const char *message);
void read_command(char *command, size_t size);
void execute_command(const char *command);


#endif
