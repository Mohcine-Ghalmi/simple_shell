#ifndef _SHELL_H_
#define _SHELL_H_
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

/* Global environemnt */
extern char **environ;
/* Global program name */
char *name;
/* Global history counter */
int hist;

/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - A new struct type defining builtin commands.
 * @name: The name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;

/* Main Helpers */
ssize_t one_line_stdin(char **lineptr, size_t *n, FILE *stream);
void *fat_calloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **tokenizer(char *line, char *delim);
char *get_location(char *command);
list_t *env_dir(char *path);
int exec(char **args, char **front);
void free_env(list_t *head);
char *ft_itoa(int num);

/* Input Helpers */
void split_line_stdin(char **line, ssize_t read);
void find_replace(char **args, int *exe_ret);
char *cmd_in(char *line, int *exe_ret);
int split_cmd(char **args, char **front, int *exe_ret);
int exec_of_cmd(char **args, char **front, int *exe_ret);
int make_cmd(int *exe_ret);
int check_fail(char **args);
void leaks(char **args, char **front);
char **replace_aliases(char **args);

/* String functions */
int ft_strlen(const char *s);
char *ft_strcat(char *dest, const char *src);
char *ft_strncat(char *dest, const char *src, size_t n);
char *ft_strcpy(char *dest, const char *src);
char *ft_strchr(char *s, char c);
int ft_length_spn(char *s, char *accept);
int ft_strcmp(char *s1, char *s2);
int ft_strncmp(const char *s1, const char *s2, size_t n);

/* Builtins */
int (*get_builtin(char *command))(char **args, char **front);
int builtins_exit(char **args, char **front);
int clone_env(char **args, char __attribute__((__unused__)) **front);
int clone_setenv(char **args, char __attribute__((__unused__)) **front);
int clone_unsetenv(char **args, char __attribute__((__unused__)) **front);
int simple_cd(char **args, char __attribute__((__unused__)) **front);
int builtins_all(char **args, char __attribute__((__unused__)) **front);
int simple_help(char **args, char __attribute__((__unused__)) **front);

/* Builtin Helpers */
char **new_env(void);
void free_env_empty(void);
char **env_key(const char *var);

/* Error Handling */
int print_stderr(char **args, int err);
char *fail_env1(char **args);
char *fail_env2(char **args);
char *fail_exit1(char **args);
char *fail_cd1(char **args);
char *fail_syntax1(char **args);
char *env_mod(char **args);
char *env_not_found(char **args);

/* Linkedlist Helpers */
alias_t *add_env(alias_t **head, char *name, char *value);
void delete_env(alias_t *head);
list_t *add_back(list_t **head, char *dir);
void free_env(list_t *head);

void builtins_print_all(void);
void builtins_print_all1(void);
void exec_cd(void);
void exec_exit(void);
void exec_help(void);
void simple_env(void);
void simple_setenv(void);
void simple_unsetenv(void);
void simple_history(void);

int exec_cmd(char *file_path, int *exe_ret);
#endif /* _SHELL_H_ */
