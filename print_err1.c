#include "simple_shell.h"

char *env_mod(char **args);
char *env_not_found(char **args);

/**
 * env_mod - Creates an error message for permission denied failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *env_mod(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = ft_itoa(hist);
	if (!hist_str)
		return (NULL);

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
	ft_strcat(error, ": ");
	ft_strcat(error, args[0]);
	ft_strcat(error, ": Permission denied\n");

	free(hist_str);
	return (error);
}

/**
 * env_not_found - Creates an error message for command not found failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *env_not_found(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = ft_itoa(hist);
	if (!hist_str)
		return (NULL);

	len = ft_strlen(name) + ft_strlen(hist_str) + ft_strlen(args[0]) + 16;
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
	ft_strcat(error, ": not found\n");

	free(hist_str);
	return (error);
}
