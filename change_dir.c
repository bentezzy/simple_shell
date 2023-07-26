#include "shell.h"

/**
 * cd_dot - fun tht changes to the parent directory
 *
 * @data_rel: data relevant (environ)
 *
 * Return: no return
 */
void cd_dot(data_shell *data_rel)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_strtok_pwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, data_rel);
	dir = data_rel->args[1];
	if (_strcmp(".", dir) == 0)
	{
		set_env("PWD", cp_pwd, data_rel);
		free(cp_pwd);
		return;
	}
	if (_strcmp("/", cp_pwd) == 0)
	{
		free(cp_pwd);
		return;
	}
	cp_strtok_pwd = cp_pwd;
	reverse_str(cp_strtok_pwd);
	cp_strtok_pwd = _strtok(cp_strtok_pwd, "/");
	if (cp_strtok_pwd != NULL)
	{
		cp_strtok_pwd = _strtok(NULL, "\0");

		if (cp_strtok_pwd != NULL)
			reverse_str(cp_strtok_pwd);
	}
	if (cp_strtok_pwd != NULL)
	{
		chdir(cp_strtok_pwd);
		set_env("PWD", cp_strtok_pwd, data_rel);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", data_rel);
	}
	data_rel->status = 0;
	free(cp_pwd);
}

/**
 * cd_to - fun tht changes to a directory given
 * by the user
 *
 * @data_rel: data relevant (directories)
 * Return: no return
 */
void cd_to(data_shell *data_rel)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = data_rel->args[1];
	if (chdir(dir) == -1)
	{
		get_error(data_rel, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	set_env("OLDPWD", cp_pwd, data_rel);

	cp_dir = _strdup(dir);
	set_env("PWD", cp_dir, data_rel);

	free(cp_pwd);
	free(cp_dir);

	data_rel->status = 0;

	chdir(dir);
}

/**
 * cd_previous - changes to the previous directory
 *
 * @data_rel: data relevant (environ)
 * Return: no return
 */
void cd_previous(data_shell *data_rel)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);

	p_oldpwd = _getenv("OLDPWD", data_rel->_environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_env("OLDPWD", cp_pwd, data_rel);

	if (chdir(cp_oldpwd) == -1)
		set_env("PWD", cp_pwd, data_rel);
	else
		set_env("PWD", cp_oldpwd, data_rel);

	p_pwd = _getenv("PWD", data_rel->_environ);

	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	data_rel->status = 0;

	chdir(p_pwd);
}

/**
 * cd_to_home - fun tht changes to home directory
 *
 * @data_rel: data relevant (environ)
 * Return: no return
 */
void cd_to_home(data_shell *data_rel)
{
	char *p_pwd, *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);

	home = _getenv("HOME", data_rel->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", p_pwd, data_rel);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(data_rel, 2);
		free(p_pwd);
		return;
	}

	set_env("OLDPWD", p_pwd, data_rel);
	set_env("PWD", home, data_rel);
	free(p_pwd);
	data_rel->status = 0;
}
