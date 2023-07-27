#include "shell.h"

/**
 * free_data - frees data structure
 *
 * @data_rel: data structure
 * Return: no return
 */
void free_data(data_shell *data_rel)
{
	unsigned int i;

	for (i = 0; data_rel->_environ[i]; i++)
	{
		free(data_rel->_environ[i]);
	}

	free(data_rel->_environ);
	free(data_rel->pid);
}

/**
 * set_data - Initialize data structure
 *
 * @data_rel: data structure
 * @av: argument vector
 * Return: no return
 */
void set_data(data_shell *data_rel, char **av)
{
	unsigned int i;

	data_rel->av = av;
	data_rel->input = NULL;
	data_rel->args = NULL;
	data_rel->status = 0;
	data_rel->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	data_rel->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		data_rel->_environ[i] = _strdup(environ[i]);
	}

	data_rel->_environ[i] = NULL;
	data_yet->pid = aux_itoa(getpid());
}

/**
 * main - Entry point
 *
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	data_shell data_rel;
	(void) ac;

	signal(SIGINT, get_sigint);
	set_data(&data_rel, av);
	shell_loop(&data_rel);
	free_data(&dat_rel);
	if (data_rel.status < 0)
		return (255);
	return (data_rel.status);
}
