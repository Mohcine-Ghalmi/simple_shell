#include "simple_shell.h"

void signales(int sig);
int exec(char **args, char **front);

/**
 * signales - Prints a new prompt upon a signal.
 * @sig: The signal.
 */
void signales(int sig)
{
	char *new_prompt = "\n$ ";

	(void)sig;
	signal(SIGINT, signales);
	write(STDIN_FILENO, new_prompt, 3);
}

/**
 * exec - execs a command in a child process.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - a corresponding error code.
 *         O/w - The exit value of the last execd command.
 */
int exec(char **args, char **front)
{
	pid_t child_pid;
	int status, flag = 0, ret = 0;
	char *command = args[0];

	if (command[0] != '/' && command[0] != '.')
	{
		flag = 1;
		command = get_location(command);
	}

	if (!command || (access(command, F_OK) == -1))
	{
		if (errno == EACCES)
			ret = (print_stderr(args, 126));
		else
			ret = (print_stderr(args, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
				free(command);
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(command, args, environ);
			if (errno == EACCES)
				ret = (print_stderr(args, 126));
			free_env_empty();
			leaks(args, front);
			delete_env(aliases);
			_exit(ret);
		}
		else
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(command);
	return (ret);
}

/**
 * main - Runs a simple UNIX command interpreter.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: The return value of the last execd command.
 */
int main(int argc, char *argv[])
{
	int ret = 0, retn;
	int *exe_ret = &retn;
	char *prompt = "$ ", *new_line = "\n";

	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, signales);

	*exe_ret = 0;
	environ = new_env();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		ret = exec_cmd(argv[1], exe_ret);
		free_env_empty();
		delete_env(aliases);
		return (*exe_ret);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (ret != END_OF_FILE && ret != EXIT)
			ret = make_cmd(exe_ret);
		free_env_empty();
		delete_env(aliases);
		return (*exe_ret);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		ret = make_cmd(exe_ret);
		if (ret == END_OF_FILE || ret == EXIT)
		{
			if (ret == END_OF_FILE)
				write(STDOUT_FILENO, new_line, 1);
			free_env_empty();
			delete_env(aliases);
			exit(*exe_ret);
		}
	}

	free_env_empty();
	delete_env(aliases);
	return (*exe_ret);
}
