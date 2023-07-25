#include "simple_shell.h"

char *env_path(char *path);
list_t *env_dir(char *path);

/**
 * get_location - Locates a command in the PATH.
 * @command: The command to locate.
 *
 * Return: If an error occurs or the command cannot be located - NULL.
 *         Otherwise - the full pathname of the command.
 */
char *get_location(char *command)
{
	char **path, *temp;
	list_t *dirs, *head;
	struct stat st;

	path = env_key("PATH");
	if (!path || !(*path))
		return (NULL);

	dirs = env_dir(*path + 5);
	head = dirs;

	while (dirs)
	{
		temp = malloc(ft_strlen(dirs->dir) + ft_strlen(command) + 2);
		if (!temp)
			return (NULL);

		ft_strcpy(temp, dirs->dir);
		ft_strcat(temp, "/");
		ft_strcat(temp, command);

		if (stat(temp, &st) == 0)
		{
			free_env(head);
			return (temp);
		}

		dirs = dirs->next;
		free(temp);
	}

	free_env(head);

	return (NULL);
}

/**
 * env_path - Copies path but also replaces leading/sandwiched/trailing
 *		   colons (:) with current working directory.
 * @path: The colon-separated list of directories.
 *
 * Return: A copy of path with any leading/sandwiched/trailing colons replaced
 *	   with the current working directory.
 */
char *env_path(char *path)
{
	int i, length = 0;
	char *path_copy, *pwd;

	pwd = *(env_key("PWD")) + 4;
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == ':' || i == 0 || path[i + 1] == '\0')
				length += ft_strlen(pwd) + 1;
			else
				length++;
		}
		else
			length++;
	}
	path_copy = malloc(sizeof(char) * (length + 1));
	if (!path_copy)
		return (NULL);
	path_copy[0] = '\0';
	for (i = 0; path[i]; i++)
	{
		if (path[i] == ':')
		{
			if (i == 0)
			{
				ft_strcat(path_copy, pwd);
				ft_strcat(path_copy, ":");
			}
			else if (path[i + 1] == ':' || path[i + 1] == '\0')
			{
				ft_strcat(path_copy, ":");
				ft_strcat(path_copy, pwd);
			}
			else
				ft_strcat(path_copy, ":");
		}
		else
		{
			ft_strncat(path_copy, &path[i], 1);
		}
	}
	return (path_copy);
}

/**
 * env_dir - Tokenizes a colon-separated list of
 *                directories into a list_s linked list.
 * @path: The colon-separated list of directories.
 *
 * Return: A pointer to the initialized linked list.
 */
list_t *env_dir(char *path)
{
	int index;
	char **dirs, *path_copy;
	list_t *head = NULL;

	path_copy = env_path(path);
	if (!path_copy)
		return (NULL);
	dirs = tokenizer(path_copy, ":");
	free(path_copy);
	if (!dirs)
		return (NULL);

	for (index = 0; dirs[index]; index++)
	{
		if (add_back(&head, dirs[index]) == NULL)
		{
			free_env(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (head);
}
