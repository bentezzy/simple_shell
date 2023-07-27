#include "shell.h"

/**
 * get_error - calls the error according the builtin, syntax or permission
 * @data_rel: data structure that contains arguments
 * @eval: error value
 * Return: error
 */
int get_error(data_shell *data_rel, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = error_env(data_rel);
		break;
	case 100:
		error = error_path_100(data_rel);
		break;
	case 127:
		error = error_not_found(data_rel);
		break;
	case 2:
		if (_strcmp("exit", data_rel->args[0]) == 0)
			error = error_exit_shell(data_rel);
		else if (_strcmp("cd", data_rel->args[0]) == 0)
			error = error_get_dir(data_rel);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	data_rel->status = eval;
	return (eval);
}
