#include "shell.h"

/**
 * copy_info - copies info to create
 * a new env or alias
 * @name: name (env or alias)
 * @value: value (env or alias)
 * calculate the lengths of names
 * Return: new env or alias.
 */
char *copy_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
 * set_env - sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @data_rel: data structure (environ)
 * Return: no return
 */
void set_env(char *name, char *value, data_shell *data_rel)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; data_rel->_environ[i]; i++)
	{
		var_env = _strdup(data_rel->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(data_rel->_environ[i]);
			data_rel->_environ[i] = copy_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}


	data_rel->_environ = _realloc_d(data_rel->_environ, i,
			sizeof(char *) * (i + 2));

	data_rel->_environ[i] = copy_info(name, value);
	data_rel->_environ[i + 1] = NULL;
}

/**
 * _setenv - compares env variables names
 * with the name passed.
 * @data_rel: data relevant (env name and env value)
 *
 * Return: 1 on success.
 */
int _setenv(data_shell *data_rel)
{

	if (data_rel->args[1] == NULL || data_rel->args[2] == NULL)
	{
		get_error(data_rel, -1);
		return (1);
	}


	set_env(data_rel->args[1], data_rel->args[2], data_rel);

	set_env(data_rel->args[1], data_rel->args[2], data_rel);


	return (1);
}

/**
 * _unsetenv - deletes a environment variable
 *
 * @data_rel: data relevant (env name)
 *
 * Return: 1 on success.
 */
int _unsetenv(data_shell *data_rel)
{
	char **realloc_environ;
	char *var_env, *name_env;
	int i, j, k;

	if (data_rel->args[1] == NULL)
	{
		get_error(data_rel, -1);
		return (1);
	}
	k = -1;
	for (i = 0; data_rel->_environ[i]; i++)
	{
		var_env = _strdup(data_rel->_environ[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, data_rel->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		get_error(data_rel, -1);
		return (1);
	}
	realloc_environ = malloc(sizeof(char *) * (i));
	for (i = j = 0; data_rel->_environ[i]; i++)
	{
		if (i != k)
		{
			realloc_environ[j] = data_rel->_environ[i];
			j++;
		}
	}
	realloc_environ[j] = NULL;

	free(data_rel->_environ[k]);
	free(data_rel->_environ);
	data_rel->_environ = realloc_environ;
	return (1);
}
