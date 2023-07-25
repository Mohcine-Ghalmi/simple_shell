#include "simple_shell.h"

char *cmd_in(char *line, int *exe_ret);
int split_cmd(char **args, char **front, int *exe_ret);
int exec_of_cmd(char **args, char **front, int *exe_ret);
int make_cmd(int *exe_ret);
int check_fail(char **args);

/**
 * cmd_in - Gets a command from standard input.
 * @line: A buffer to store the command.
 * @exe_ret: The return value of the last execd command.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the stored command.
 */
char *cmd_in(char *line, int *exe_ret)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (line)
		free(line);

	read = one_line_stdin(&line, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (cmd_in(line, exe_ret));
	}

	line[read - 1] = '\0';
	find_replace(&line, exe_ret);
	split_line_stdin(&line, read);

	return (line);
}

/**
 * split_cmd - Partitions operators from commands and calls them.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * @exe_ret: The return value of the parent process' last execd command.
 *
 * Return: The return value of the last execd command.
 */
int split_cmd(char **args, char **front, int *exe_ret)
{
	int ret, index;

	if (!args[0])
		return (*exe_ret);
	for (index = 0; args[index]; index++)
	{
		if (ft_strncmp(args[index], "||", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_aliases(args);
			ret = exec_of_cmd(args, front, exe_ret);
			if (*exe_ret != 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (ret);
			}
		}
		else if (ft_strncmp(args[index], "&&", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_aliases(args);
			ret = exec_of_cmd(args, front, exe_ret);
			if (*exe_ret == 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (ret);
			}
		}
	}
	args = replace_aliases(args);
	ret = exec_of_cmd(args, front, exe_ret);
	return (ret);
}

/**
 * exec_of_cmd - Calls the execution of a command.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * @exe_ret: The return value of the parent process' last execd command.
 *
 * Return: The return value of the last execd command.
 */
int exec_of_cmd(char **args, char **front, int *exe_ret)
{
	int ret, i;
	int (*builtin)(char **args, char **front);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		ret = builtin(args + 1, front);
		if (ret != EXIT)
			*exe_ret = ret;
	}
	else
	{
		*exe_ret = exec(args, front);
		ret = *exe_ret;
	}

	hist++;

	for (i = 0; args[i]; i++)
		free(args[i]);

	return (ret);
}

/**
 * make_cmd - Gets, calls, and runs the execution of a command.
 * @exe_ret: The return value of the parent process' last execd command.
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         O/w - The exit value of the last execd command.
 */
int make_cmd(int *exe_ret)
{
	int ret = 0, index;
	char **args, *line = NULL, **front;

	line = cmd_in(line, exe_ret);
	if (!line)
		return (END_OF_FILE);

	args = tokenizer(line, " ");
	free(line);
	if (!args)
		return (ret);
	if (check_fail(args) != 0)
	{
		*exe_ret = 2;
		leaks(args, args);
		return (*exe_ret);
	}
	front = args;

	for (index = 0; args[index]; index++)
	{
		if (ft_strncmp(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			ret = split_cmd(args, front, exe_ret);
			args = &args[++index];
			index = 0;
		}
	}
	if (args)
		ret = split_cmd(args, front, exe_ret);

	free(front);
	return (ret);
}

/**
 * check_fail - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @args: 2D pointer to tokenized commands and arguments.
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
 *	   Otherwise - 0.
 */
int check_fail(char **args)
{
	size_t i;
	char *cur, *nex;

	for (i = 0; args[i]; i++)
	{
		cur = args[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (print_stderr(&args[i], 2));
			nex = args[i + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (print_stderr(&args[i + 1], 2));
		}
	}
	return (0);
}
