#include "shell.h"

/**
 * get_help - function that retrieves help messages according builtin
 * @data_rel: data structure (args and input)
 * Return: Return 0
*/
int get_help(data_shell *data_rel)
{

	if (data_rel->args[1] == 0)
		my_help_general();
	else if (_strcmp(data_rel->args[1], "setenv") == 0)
		my_help_setenv();
	else if (_strcmp(data_rel->args[1], "env") == 0)
		my_help_env();
	else if (_strcmp(data_rel->args[1], "unsetenv") == 0)
		my_help_unsetenv();
	else if (_strcmp(data_rel->args[1], "help") == 0)
		my_help();
	else if (_strcmp(data_rel->args[1], "exit") == 0)
		my_help_exit();
	else if (_strcmp(data_rel->args[1], "cd") == 0)
		my_help_cd();
	else if (_strcmp(data_rel->args[1], "alias") == 0)
		my_help_alias();
	else
		write(STDERR_FILENO, data_rel->args[0],
		      _strlen(data_rel->args[0]));

	data_rel->status = 0;
	return (1);
}
