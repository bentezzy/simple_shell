#include "shell.h"

/**
 * strcat_dir - fun that concatenates the message for dir error
 *
 * @data_rel: relevant data to dir
 * @mess: message to print
 * @error: message to be output
 * @count: for counter lines
 * Return: error message
 */
char *strcat_dir(data_shell *data_rel, char *mess, char *error, char *count)
{
	char *irrelevant_flag;

	_strcpy(error, data_rel->av[0]);
	_strcat(error, ": ");
	_strcat(error, count);
	_strcat(error, ": ");
	_strcat(error, data_rel->args[0]);
	_strcat(error, mess);
	if (data_rel->args[1][0] == '-')
	{
		irrelevant_flag = malloc(3);
		irrelevant_flag[0] = '-';
		irrelevant_flag[1] = datash->args[1][1];
		irrelevant_flag[2] = '\0';
		_strcat(error, irrelevant_flag);
		free(irrelevant_flag);
	}
	else
	{
		_strcat(error, data_rel->args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * error_get_dir - error message for cd command in get_cd
 * @data_rel: data relevant (directory)
 * Return: Error message
 */
char *error_get_dir(data_shell *data_rel)
{
	int leng, leng_id;
	char *error, *count, *mess;

	count = aux_itoa(data_rel->counter);
	if (data_rel->args[1][0] == '-')
	{
		mess = ": Irrelevant option ";
		leng_id = 2;
	}
	else
	{
		mess = ": can't cd to ";
		leng_id = _strlen(data_rel->args[1]);
	}

	leng = _strlen(data_rel->av[0]) + _strlen(data_rel->args[0]);
	leng += _strlen(count) + _strlen(mess) + leng_id + 5;
	error = malloc(sizeof(char) * (leng + 1));

	if (error == 0)
	{
		free(count);
		return (NULL);
	}

	error = strcat_dir(data_rel, mess, error, count);

	free(count);

	return (error);
}

/**
 * error_not_found - generic error message for command not found
 * @data_rel: data relevant (counter, arguments)
 * Return: Error message
 */
char *error_not_found(data_shell *data_rel)
{
	int leng;
	char *error;
	char *count;

	count = aux_itoa(data_rel->counter);
	leng = _strlen(data_rel->av[0]) + _strlen(count);
	leng += _strlen(data_rel->args[0]) + 16;
	error = malloc(sizeof(char) * (leng + 1));
	if (error == 0)
	{
		free(error);
		free(count);
		return (NULL);
	}
	_strcpy(error, data_rel->av[0]);
	_strcat(error, ": ");
	_strcat(error, count);
	_strcat(error, ": ");
	_strcat(error, data_rel->args[0]);
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(count);
	return (error);
}

/**
 * error_exit_shell - generic error message for exit in get_exit
 * @data_rel: data relevant (counter, arguments)
 *
 * Return: Error message
 */
char *error_exit_shell(data_shell *data_rel)
{
	int leng;
	char *error;
	char *count;

	count = aux_itoa(data_rel->counter);
	leng = _strlen(data_rel->av[0]) + _strlen(ver_str);
	leng += _strlen(data_rel->args[0]) + _strlen(data_rel->args[1]) + 23;
	error = malloc(sizeof(char) * (leng + 1));
	if (error == 0)
	{
		free(count);
		return (NULL);
	}
	_strcpy(error, data_rel->av[0]);
	_strcat(error, ": ");
	_strcat(error, count);
	_strcat(error, ": ");
	_strcat(error, data_rel->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, data_rel->args[1]);
	_strcat(error, "\n\0");
	free(count);

	return (error);
}
