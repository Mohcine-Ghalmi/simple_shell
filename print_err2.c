#include "simple_shell.h"

int ft_putnbr_size(int num);
char *ft_itoa(int num);
int print_stderr(char **args, int err);

/**
 * ft_putnbr_size - Counts the digit length of a number.
 * @num: The number to measure.
 *
 * Return: The digit length.
 */
int ft_putnbr_size(int num)
{
	unsigned int num1;
	int len = 1;

	if (num < 0)
	{
		len++;
		num1 = num * -1;
	}
	else
	{
		num1 = num;
	}
	while (num1 > 9)
	{
		len++;
		num1 /= 10;
	}

	return (len);
}

/**
 * ft_itoa - Converts an integer to a string.
 * @num: The integer.
 *
 * Return: The converted string.
 */
char *ft_itoa(int num)
{
	char *buffer;
	int len = ft_putnbr_size(num);
	unsigned int num1;

	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);

	buffer[len] = '\0';

	if (num < 0)
	{
		num1 = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num1 = num;
	}

	len--;
	do {
		buffer[len] = (num1 % 10) + '0';
		num1 /= 10;
		len--;
	} while (num1 > 0);

	return (buffer);
}


/**
 * print_stderr - Writes a custom error message to stderr.
 * @args: An array of arguments.
 * @err: The error value.
 *
 * Return: The error value.
 */
int print_stderr(char **args, int err)
{
	char *error;

	switch (err)
	{
	case -1:
		error = fail_env1(args);
		break;
	case 1:
		error = fail_env2(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			error = fail_exit1(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			error = fail_syntax1(args);
		else
			error = fail_cd1(args);
		break;
	case 126:
		error = env_mod(args);
		break;
	case 127:
		error = env_not_found(args);
		break;
	}
	write(STDERR_FILENO, error, ft_strlen(error));

	if (error)
		free(error);
	return (err);

}
