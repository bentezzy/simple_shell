#include "shell.h"

/**
 * exit_shell -fun tht  exits the shell
 *
 * @data_rel: data relevant (status and args)
 * Return: 0 on success.
 */
int exit_shell(data_shell *data_rel)
{
	unsigned int ustatus;
	int is_digit;
	int str_len;
	int big_number;

	if (data_rel->args[1] != NULL)
	{
		ustatus = _atoi(data_rel->args[1]);
		is_digit = _isdigit(data_rel->args[1]);
		str_len = _strlen(data_rel->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || big_number)
		{
			get_error(data_rel, 2);
			data_rel->status = 2;
			return (1);
		}
		data_rel->status = (ustatus % 256);
	}
	return (0);
}
