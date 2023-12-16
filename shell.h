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

/* This is for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* This is for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* This for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str:  string
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


/* Function prototypes */
int chain_delim(info_t *info, char *buf, size_t *p);
void scan_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int rep_alias(info_t *info);
int new_vars(info_t *info);
int str_change(char **old, char *new);
char **split_str2(char *str, char d);
char **split_str(char *str, char *d);
int _putchar(char c);
void my_print(char *str);
char *strd_up(const char *str);
char *copy_str(char *dest, char *src);
int str_length(char *s);
int str_cmp(char *s1, char *s2);
char *_startswith(const char *shell, const char *command);
char *str_cnct(char *dest, char *src);
char *str_cnct(char *dest, char *src);
int hsh(inf_t *info, char **av);
int disc_builtin(info_t *info);
void disc_cmd(inf_t *info);
void exec_fork(info_t *info);
char *shell_memset(char *s, char b, unsigned int n);
void free_str(char **pp);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int is_cmd(info_t *info, char *path);
char *copy_chars(char *pathstr, int begin, int end);
char *disc_path(inf_t *inf, char *pathstr, char *cmd);
int be_free(void **ptr);
int main(int ac, char **av);
size_t length_list(const list_t *h);
char **strings_lists(list_t *head);
size_t my_printList(const list_t *h);
list_t *node_create(list_t *node, char *prefix, char c);
ssize_t get_index_node(list_t *head, list_t *node);
list_t *node_next(list_t **head, const char *str, int num);
list_t *add_end_node(list_t **head, const char *str, int num);
size_t myprint_listStr(const list_t *h);
int node_del_index(list_t **head, unsigned int index);
void node_list_free(list_t **head_ptr);
char *get_his_file(info_t *info);
int write_hist(info_t *info);
int scan_his(info_t *info);
int make_his_list(info_t *info, char *buf, int linecount);
int new_numHis(info_t *info);
ssize_t my_inputBuf(info_t *info, char **buf, size_t *len);
ssize_t input_line(info_t *info);
ssize_t search_buf(info_t *info, char *buf, size_t *i);
int get_line(info_t *info, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused))int sig_num);
void init_inf(info_t *info);
void put_inf(info_t *info, char **av);
void rem_inf(info_t *info, int all);
char **get_environ(info_t *info);
int unset_env(info_t *info, char *var);
int set_env(inf_t *info, char *var, char *value);
char *string_copy(char *dest, char *src, int n);
char *strn_cat(char *dest, char *src, int n);
char *str_char(char *s, char c);
int erra_toi(char *s);
void my_printError(info_t *info, char *estr);
int dec_print(int input, int fd);
char *convrt_num(long int num, int base, int flags);
void rem_comments(char *buf);
void emy_print(char *str);
int _eputchar(char c);
int my_printfd(char c, int fd);
int my_printfd(char *str, int fd);
int shell_env(info_t *info);
char *get_env(info_t *info, const char *name);
int shell_setenv(info_t *info);
int shell_unsetenv(info_t *info);
int pop_env_list(info_t *info);
int shell_history(info_t *info);
int unset_alias(info_t *info, char *str);
int set_alias(info_t *info, char *str);
int my_printAlias(list_t *node);
int shell_alias(info_t *info);
int my_cd(info_t *info);
int shell_exit(info_t *info);
int shell_help(info_t *info);
int interactive(info_t *info);
int _delim(char c, char *delim);
int is_alpha(int c);
int shell_atoi(char *s);

#endif

