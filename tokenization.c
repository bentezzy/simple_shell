#include "shell.h"

/**
 * _strdup - Duplicates a strng in the heap memory.
 * @s: Type char pointer str
 * Return: duplicated str
 */
char *_strdup(const char *s)
{
	char *fresh;
	size_t lengt;

	lengt = _strlen(s);
	fresh = malloc(sizeof(char) * (lengt + 1));
	if (fresh == NULL)
		return (NULL);
	_memcpy(fresh, s, lengt + 1);
	return (fresh);
}

/**
 * _strlen - fun that Returns the lenghth of a string.
 * @s: Type char pointer
 * Return: Always 0.
 */
int _strlen(const char *s)
{
	int lengt;

	for (lengt = 0; s[lengt] != 0; lengt++)
	{
	}
	return (lengt);
}

/**
 * cmp_char - fun that compare chars of strings
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: 1 if are equals, 0 if not.
 */
int cmp_char(char str[], const char *delim)
{
	unsigned int a, b, d;

	for (a = 0, d = 0; str[a]; a++)
	{
		for (b = 0; delim[b]; b++)
		{
			if (str[a] == delim[b])
			{
				d++;
				break;
			}
		}
	}
	if (a == d)
		return (1);
	return (0);
}

/**
 * _strtok - fun tht splits a string by some delimiter.
 * @str: input string.
 * @delim: delimiter.
 *
 * Return: string splited.
 */
char *_strtok(char str[], const char *delim)
{
	static char *split, *str_end;
	char *str_start;
	unsigned int a, bool;

	if (str != NULL)
	{
		if (cmp_char(str, delim))
			return (NULL);
		split = str; /*Store first address*/
		a = _strlen(str);
		str_end = &str[a]; /*Store last address*/
	}
	str_start = split;
	if (str_start == str_end) /*Reaching the end*/
		return (NULL);

	for (bool = 0; *split; split++)
	{
		/*Breaking loop finding the next token*/
		if (split != str_start)
			if (*split && *(split - 1) == '\0')
				break;
		/*Replacing delimiter for null char*/
		for (a = 0; delim[a]; a++)
		{
			if (*split == delim[a])
			{
				*split = '\0';
				if (split == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *split) /*Str != Delim*/
			bool = 1;
	}
	if (bool == 0) /*Str == Delim*/
		return (NULL);
	return (str_start);
}

/**
 * _isdigit - fun tht defines if string passed is a number
 *
 * @s: input string
 * Return: 1 if string is a number. 0 in other case.
 */
int _isdigit(const char *s)
{
	unsigned int a;

	for (a = 0; s[a]; a++)
	{
		if (s[a] < 48 || s[a] > 57)
			return (0);
	}
	return (1);
}
