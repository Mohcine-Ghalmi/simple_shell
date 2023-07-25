#include "simple_shell.h"

char *fail_env1(char **args);
char *fail_env2(char **args);
char *fail_exit1(char **args);
char *fail_cd1(char **args);
char *fail_syntax1(char **args);
/**
 * fail_env1 - Creates an error message for clone_env errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *fail_env1(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = ft_itoa(hist);
	if (!hist_str)
		return (NULL);

	args--;
	len = ft_strlen(name) + ft_strlen(hist_str) + ft_strlen(args[0]) + 45;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	ft_strcpy(error, name);
	ft_strcat(error, ": ");
	ft_strcat(error, hist_str);
	ft_strcat(error, ": ");
	ft_strcat(error, args[0]);
	ft_strcat(error, ": Unable to add/remove from environment\n");

	free(hist_str);
	return (error);
}

/**
 * fail_env2 - Creates an error message for builtins_all errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *fail_env2(char **args)
{
	char *error;
	int len;

	len = ft_strlen(name) + ft_strlen(args[0]) + 13;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
		return (NULL);

	ft_strcpy(error, "alias: ");
	ft_strcat(error, args[0]);
	ft_strcat(error, " not found\n");

	return (error);
}

/**
 * fail_exit1 - Creates an error message for builtins_exit errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *fail_exit1(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = ft_itoa(hist);
	if (!hist_str)
		return (NULL);

	len = ft_strlen(name) + ft_strlen(hist_str) + ft_strlen(args[0]) + 27;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	ft_strcpy(error, name);
	ft_strcat(error, ": ");
	ft_strcat(error, hist_str);
	ft_strcat(error, ": exit: Illegal number: ");
	ft_strcat(error, args[0]);
	ft_strcat(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * fail_cd1 - Creates an error message for simple_cd errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *fail_cd1(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = ft_itoa(hist);
	if (!hist_str)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
	len = ft_strlen(name) + ft_strlen(hist_str) + ft_strlen(args[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	ft_strcpy(error, name);
	ft_strcat(error, ": ");
	ft_strcat(error, hist_str);
	if (args[0][0] == '-')
		ft_strcat(error, ": cd: Illegal option ");
	else
		ft_strcat(error, ": cd: can't cd to ");
	ft_strcat(error, args[0]);
	ft_strcat(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * fail_syntax1 - Creates an error message for syntax errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *fail_syntax1(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = ft_itoa(hist);
	if (!hist_str)
		return (NULL);

	len = ft_strlen(name) + ft_strlen(hist_str) + ft_strlen(args[0]) + 33;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	ft_strcpy(error, name);
	ft_strcat(error, ": ");
	ft_strcat(error, hist_str);
	ft_strcat(error, ": Syntax error: \"");
	ft_strcat(error, args[0]);
	ft_strcat(error, "\" unexpected\n");

	free(hist_str);
	return (error);
}
