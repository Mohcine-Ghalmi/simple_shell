#include "simple_shell.h"

void builtins_print_all(void);
void builtins_print_all1(void);
void exec_cd(void);
void exec_exit(void);
void exec_help(void);

/**
 * builtins_print_all - Displays all possible builtin shellby commands.
 */
void builtins_print_all(void)
{
	char *msg = "Shellby\nThese shell commands are defined internally.\n";

	write(STDOUT_FILENO, msg, ft_strlen(msg));
	msg = "Type 'help' to see this list.\nType 'help name' to find ";
	write(STDOUT_FILENO, msg, ft_strlen(msg));
	msg = "out more about the function 'name'.\n\n  alias   \t";
	write(STDOUT_FILENO, msg, ft_strlen(msg));
	msg = "alias [NAME[='VALUE'] ...]\n  cd    \tcd   ";
	write(STDOUT_FILENO, msg, ft_strlen(msg));
	msg = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";
	write(STDOUT_FILENO, msg, ft_strlen(msg));
	msg = "\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";
	write(STDOUT_FILENO, msg, ft_strlen(msg));
	msg = "unsetenv [VARIABLE]\n";
	write(STDOUT_FILENO, msg, ft_strlen(msg));
}

/**
 * builtins_print_all1 - Displays information on the shellby builtin command 'alias'.
 */
void builtins_print_all1(void)
{
	char *msg = "alias: alias [NAME[='VALUE'] ...]\n\tHandles aliases.\n";

	write(STDOUT_FILENO, msg, ft_strlen(msg));
	msg = "\n\talias: Prints a list of all aliases, one per line, in ";
	write(STDOUT_FILENO, msg, ft_strlen(msg));
	msg = "the format NAME='VALUE'.\n\talias name [name2 ...]:prints";
	write(STDOUT_FILENO, msg, ft_strlen(msg));
	msg = " the aliases name, name2, etc. one per line, in the ";
	write(STDOUT_FILENO, msg, ft_strlen(msg));
	msg = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Defines";
	write(STDOUT_FILENO, msg, ft_strlen(msg));
	msg = " an alias for each NAME whose VALUE is given. If NAME ";
	write(STDOUT_FILENO, msg, ft_strlen(msg));
	msg = "is already an alias, replace its value with VALUE.\n";
	write(STDOUT_FILENO, msg, ft_strlen(msg));
}

/**
 * exec_cd - Displays information on the shellby builtin command 'cd'.
 */
void exec_cd(void)
{
	char *msg = "cd: cd [DIRECTORY]\n\tChanges the current directory of the";

	write(STDOUT_FILENO, msg, ft_strlen(msg));
	msg = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
	write(STDOUT_FILENO, msg, ft_strlen(msg));
	msg = "command is interpreted as cd $HOME. If the argument '-' is";
	write(STDOUT_FILENO, msg, ft_strlen(msg));
	msg = " given, the command is interpreted as cd $OLDPWD.\n\n";
	write(STDOUT_FILENO, msg, ft_strlen(msg));
	msg = "\tThe environment variables PWD and OLDPWD are updated ";
	write(STDOUT_FILENO, msg, ft_strlen(msg));
	msg = "after a change of directory.\n";
	write(STDOUT_FILENO, msg, ft_strlen(msg));
}

/**
 * exec_exit - Displays information on the shellby builtin command 'exit'.
 */
void exec_exit(void)
{
	char *msg = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

	write(STDOUT_FILENO, msg, ft_strlen(msg));
	msg = "STATUS argument is the integer used to exit the shell.";
	write(STDOUT_FILENO, msg, ft_strlen(msg));
	msg = " If no argument is given, the command is interpreted as";
	write(STDOUT_FILENO, msg, ft_strlen(msg));
	msg = " exit 0.\n";
	write(STDOUT_FILENO, msg, ft_strlen(msg));
}

/**
 * exec_help - Displays information on the shellby builtin command 'help'.
 */
void exec_help(void)
{
	char *msg = "help: help\n\tSee all possible Shellby builtin commands.\n";

	write(STDOUT_FILENO, msg, ft_strlen(msg));
	msg = "\n      help [BUILTIN NAME]\n\tSee specific information on each ";
	write(STDOUT_FILENO, msg, ft_strlen(msg));
	msg = "builtin command.\n";
	write(STDOUT_FILENO, msg, ft_strlen(msg));
}
