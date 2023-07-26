#include <stdio.h>

#include "shell.h"

/**
 * exec_line - finds builtins and commands
 *
 * @data_rel: data relevant (args)
 * parsed command line
 * Return: 1 on success.
 */
int exec_line(data_shell *data_rel)
{
	int (*builtin)(data_shell *data_rel);

	if (data_rel->args[0] == NULL)
		return (1);

	builtin = get_builtin(data_rel->args[0]);

	if (builtin != NULL)
		return (builtin(data_rel));

	return (cmd_exec(data_rel));
}
