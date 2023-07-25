#include "simple_shell.h"

void simple_env(void);
void simple_setenv(void);
void simple_unsetenv(void);
void simple_history(void);

/**
 * simple_env - Displays information on the shellby builtin command 'env'.
 */
void simple_env(void)
{
	char *msg = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, msg, ft_strlen(msg));
}

/**
 * simple_setenv - Displays information on the shellby builtin command 'setenv'.
 */
void simple_setenv(void)
{
	char *msg = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, msg, ft_strlen(msg));
	msg = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, msg, ft_strlen(msg));
	msg = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, msg, ft_strlen(msg));
}

/**
 * simple_unsetenv - Displays information on the shellby builtin command
 * 'unsetenv'.
 */
void simple_unsetenv(void)
{
	char *msg = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, msg, ft_strlen(msg));
	msg = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, msg, ft_strlen(msg));
	msg = "message to stderr.\n";
	write(STDOUT_FILENO, msg, ft_strlen(msg));
}
