#include "shell.h"

/**
 * error_environ - error message for env in get_env.
 * @data_rel: data relevant (counter, arguments)
 * Return: error message.
 */
char *error_environ(data_shell *data_rel)
{
	int leng;
	char *error;
	char *count;
	char *mess;

	count = aux_itoa(data_rel->counter);
	mess = ": Unable to add/remove from environment\n";
	leng = _strlen(data_rel->av[0]) + _strlen(count);
	leng += _strlen(data_rel->args[0]) + _strlen(mess) + 4;
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
	_strcat(error, mess);
	_strcat(error, "\0");
	free(count);

	return (error);
}
/**
 * error_path_100 - error message for path and failure denied permission.
 * @data_rel: data relevant (counter, arguments).
 *
 * Return: error string.
 */
char *error_path_100(data_shell *data_rel)
{
	int leng;
	char *count;
	char *error;

	count = aux_itoa(data_rel->counter);
	leng = _strlen(data_rel->av[0]) + _strlen(count);
	leng += _strlen(data_rel->args[0]) + 24;
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
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(count);
	return (error);
}
