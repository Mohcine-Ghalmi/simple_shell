#include "simple_shell.h"

void leaks(char **args, char **front);
char *take_procid(void);
char *return_value(char *beginning, int len);
void find_replace(char **args, int *exe_ret);

/**
 * leaks - Frees up memory taken by args.
 * @args: A null-terminated double pointer containing commands/arguments.
 * @front: A double pointer to the beginning of args.
 */
void leaks(char **args, char **front)
{
	size_t i;

	for (i = 0; args[i] || args[i + 1]; i++)
		free(args[i]);

	free(front);
}

/**
 * take_procid - Gets the current process ID.
 * Description: Opens the stat file, a space-delimited file containing
 *              information about the current process. The PID is the
 *              first word in the file. The function reads the PID into
 *              a buffer and replace the space at the end with a \0 byte.
 *
 * Return: The current process ID or NULL on failure.
 */
char *take_procid(void)
{
	size_t i = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[i] != ' ')
		i++;
	buffer[i] = '\0';

	close(file);
	return (buffer);
}

/**
 * return_value - Gets the value corresponding to an environmental variable.
 * @beginning: The environmental variable to search for.
 * @len: The length of the environmental variable to search for.
 *
 * Return: If the variable is not found - an empty string.
 *         Otherwise - the value of the environmental variable.
 *
 * Description: Variables are stored in the format VARIABLE=VALUE.
 */
char *return_value(char *beginning, int len)
{
	char **var_addr;
	char *replacement = NULL, *temp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	ft_strncat(var, beginning, len);

	var_addr = env_key(var);
	free(var);
	if (var_addr)
	{
		temp = *var_addr;
		while (*temp != '=')
			temp++;
		temp++;
		replacement = malloc(ft_strlen(temp) + 1);
		if (replacement)
			ft_strcpy(replacement, temp);
	}

	return (replacement);
}

/**
 * find_replace - Handles variable replacement.
 * @line: A double pointer containing the command and arguments.
 * @exe_ret: A pointer to the return value of the last execd command.
 *
 * Description: Replaces $$ with the current PID, $? with the return value
 *              of the last execd program, and envrionmental variables
 *              preceded by $ with their corresponding value.
 */
void find_replace(char **line, int *exe_ret)
{
	int j, k = 0, len;
	char *replacement = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (j = 0; old_line[j]; j++)
	{
		if (old_line[j] == '$' && old_line[j + 1] &&
				old_line[j + 1] != ' ')
		{
			if (old_line[j + 1] == '$')
			{
				replacement = take_procid();
				k = j + 2;
			}
			else if (old_line[j + 1] == '?')
			{
				replacement = ft_itoa(*exe_ret);
				k = j + 2;
			}
			else if (old_line[j + 1])
			{
				/* extract the variable name to search for */
				for (k = j + 1; old_line[k] &&
						old_line[k] != '$' &&
						old_line[k] != ' '; k++)
					;
				len = k - (j + 1);
				replacement = return_value(&old_line[j + 1], len);
			}
			new_line = malloc(j + ft_strlen(replacement)
					  + ft_strlen(&old_line[k]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			ft_strncat(new_line, old_line, j);
			if (replacement)
			{
				ft_strcat(new_line, replacement);
				free(replacement);
				replacement = NULL;
			}
			ft_strcat(new_line, &old_line[k]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			j = -1;
		}
	}
}
