#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* Used For command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* Used Fot convrt_num() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/*  getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - This is a singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_swapped: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_swapped;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/*Prototypes 1 for hsh file */
int hsh(info_t *, char **);
int disc_builtin(info_t *);
void disc_cmd(info_t *);
void exec_fork(info_t *);

/* Prototypes for pars.c */
int _cmd(info_t *, char *);
char *copy_chars(char *, int, int);
char *disc_path(info_t *, char *, char *);

/*  */
int loophsh(char **);

/* Prototypes for errs.c */
void emy_print(char *);
int _eputchar(char);
int my_printsfd(char c, int fd);
int my_printfd(char *str, int fd);

/* Prototype for strr.c */
int str_length(char *);
int str_cmp(char *, char *);
char *begins_with(const char *, const char *);
char *str_cat(char *, char *);

/* Prototypes for strr1.c */
char *copy_str(char *, char *);
char *strd_up(const char *);
void my_print(char *);
int _putchar(char);

/*Prototype for exit.c */
char *strn_copy(char *, char *, int);
char *strn_cat(char *, char *, int);
char *str_char(char *, char);

/* Prototypes for token.c */
char **split_str(char *, char *);
char **split_str2(char *, char);

/* Prototype for reall.c */
char *shell_memset(char *, char, unsigned int);
void ffree(char **);
void *shell_realloc(void *, unsigned int, unsigned int);

/* Prototype for mem.c */
int bfree(void **);

/* Prototype for atoi.c */
int interactive(info_t *);
int _delim(char, char *);
int _alpha(int);
int atoi_(char *);

/* Prototypes for err1.c */
int erra_toi(char *);
void my_printError(info_t *, char *);
int dec_print(int, int);
char *convrt_num(long int, int, int);
void rem_comments(char *);

/* Prototype for builtin.c */
int shell_exit(info_t *);
int shell_cd(info_t *);
int shell_help(info_t *);

/* Prototype for builtin1.c */
int shell_history(info_t *);
int shell_alias(info_t *);

/*Prototypes for get_line.c */
ssize_t input_line(info_t *);
int get_line(info_t *, char **, size_t *);
void sigintHandler(int);

/* Prototype for get_info.c */
void init_info(info_t *);
void put_info(info_t *, char **);
void rem_info(info_t *, int);

/* Prototype for env.c */
char *get_env(info_t *, const char *);
int shell_env(info_t *);
int shell_setenv(info_t *);
int shell_unsetenv(info_t *);
int pop_list_env(info_t *);

/* Prototypes for  */
char **get_environ(info_t *);
int unset_env(info_t *, char *);
int set_env(info_t *, char *, char *);

/* Prototypes for history.c */
char *get_his_file(info_t *info);
int write_his(info_t *info);
int scan_his(info_t *info);
int make_his_list(info_t *info, char *buf, int linecount);
int new_numHis(info_t *info);

/* Prototype for list.c */
list_t *node_next(list_t **, const char *, int);
list_t *add_end_node(list_t **, const char *, int);
size_t myprint_listStr(const list_t *);
int node_del_index(list_t **, unsigned int);
void node_list_free(list_t **);

/* Prototypes for list1.c */
size_t length_list(const list_t *);
char **string_list(list_t *);
size_t my_printList(const list_t *);
list_t *node_begins_with(list_t *, char *, char);
ssize_t get_index_node(list_t *, list_t *);

/* Prototype for vars.c */
int _chain(info_t *, char *, size_t *);
void scan_chain(info_t *, char *, size_t *, size_t, size_t);
int change_alias(info_t *);
int change_vars(info_t *);
int change_string(char **, char *);

#endif

