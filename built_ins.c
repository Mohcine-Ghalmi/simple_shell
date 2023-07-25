#include "simple_shell.h"

int builtins_all(char **args, char __attribute__((__unused__)) **front);
void give_builtins(char *var_name, char *value);
void print_builtin(alias_t *alias);

/**
 * builtins_all - Builtin command that either prints all aliases, specific
 * aliases, or sets an alias.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int builtins_all(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *temp = aliases;
	int i, ret = 0;
	char *value;

	if (!args[0])
	{
		while (temp)
		{
			print_builtin(temp);
			temp = temp->next;
		}
		return (ret);
	}
	for (i = 0; args[i]; i++)
	{
		temp = aliases;
		value = ft_strchr(args[i], '=');
		if (!value)
		{
			while (temp)
			{
				if (ft_strcmp(args[i], temp->name) == 0)
				{
					print_builtin(temp);
					break;
				}
				temp = temp->next;
			}
			if (!temp)
				ret = print_stderr(args + i, 1);
		}
		else
			give_builtins(args[i], value);
	}
	return (ret);
}

/**
 * give_builtins - Will either set an existing alias 'name' with a new value,
 * 'value' or creates a new alias with 'name' and 'value'.
 * @var_name: Name of the alias.
 * @value: Value of the alias. First character is a '='.
 */
void give_builtins(char *var_name, char *value)
{
	alias_t *temp = aliases;
	int len, j, k;
	char *new_value;

	*value = '\0';
	value++;
	len = ft_strlen(value) - ft_length_spn(value, "'\"");
	new_value = malloc(sizeof(char) * (len + 1));
	if (!new_value)
		return;
	for (j = 0, k = 0; value[j]; j++)
	{
		if (value[j] != '\'' && value[j] != '"')
			new_value[k++] = value[j];
	}
	new_value[k] = '\0';
	while (temp)
	{
		if (ft_strcmp(var_name, temp->name) == 0)
		{
			free(temp->value);
			temp->value = new_value;
			break;
		}
		temp = temp->next;
	}
	if (!temp)
		add_env(&aliases, var_name, new_value);
}

/**
 * print_builtin - Prints the alias in the format name='value'.
 * @alias: Pointer to an alias.
 */
void print_builtin(alias_t *alias)
{
	char *alias_string;
	int len = ft_strlen(alias->name) + ft_strlen(alias->value) + 4;

	alias_string = malloc(sizeof(char) * (len + 1));
	if (!alias_string)
		return;
	ft_strcpy(alias_string, alias->name);
	ft_strcat(alias_string, "='");
	ft_strcat(alias_string, alias->value);
	ft_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, len);
	free(alias_string);
}
/**
 * replace_aliases - Goes through the arguments and replace any matching alias
 * with their value.
 * @args: 2D pointer to the arguments.
 *
 * Return: 2D pointer to the arguments.
 */
char **replace_aliases(char **args)
{
	alias_t *temp;
	int i;
	char *new_value;

	if (ft_strcmp(args[0], "alias") == 0)
		return (args);
	for (i = 0; args[i]; i++)
	{
		temp = aliases;
		while (temp)
		{
			if (ft_strcmp(args[i], temp->name) == 0)
			{
				new_value = malloc(sizeof(char) * (ft_strlen(temp->value) + 1));
				if (!new_value)
				{
					leaks(args, args);
					return (NULL);
				}
				ft_strcpy(new_value, temp->value);
				free(args[i]);
				args[i] = new_value;
				i--;
				break;
			}
			temp = temp->next;
		}
	}

	return (args);
}
