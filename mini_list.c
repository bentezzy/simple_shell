#include "shell.h"

/**
 * _sep_node_end - adds a separater found at the end
 * of a sep_list.
 * @head:  linked list head.
 * @sep: separator found (; | &).
 * Return: address of the head.
 */
sep_list *_sep_node_end(sep_list **head, char sep)
{
	sep_list *fresh, *tem;

	fresh = malloc(sizeof(sep_list));
	if (fresh == NULL)
		return (NULL);

	fresh->separator = sep;
	fresh->next = NULL;
	tem = *head;

	if (tem == NULL)
	{
		*head = fresh;
	}
	else
	{
		while (tem->next != NULL)
			tem = tem->next;
		tem->next = fresh;
	}

	return (*head);
}

/**
 * free_sep_list - frees a sep_list
 * @head: linked list head.
 * Return: no return.
 */
void free_sep_list(sep_list **head)
{
	sep_list *tem;
	sep_list *current;

	if (head != NULL)
	{
		current = *head;
		while ((tem = current) != NULL)
		{
			current = current->next;
			free(tem);
		}
		*head = NULL;
	}
}

/**
 * _line_node_end - adds a command line at the end
 * of a line_list.
 * @head:  linked list head.
 * @line: command line.
 * Return: address of the head.
 */
line_list *_line_node_end(line_list **head, char *line)
{
	line_list *fresh, *tem;

	fresh = malloc(sizeof(line_list));
	if (fresh == NULL)
		return (NULL);

	fresh->line = line;
	fresh->next = NULL;
	tem = *head;

	if (tem == NULL)
	{
		*head = fresh;
	}
	else
	{
		while (tem->next != NULL)
			tem = tem->next;
		tem->next = fresh;
	}

	return (*head);
}

/**
 * free_line_list - frees a line_list
 * @head: linked list head.
 * Return: no return.
 */
void free_line_list(line_list **head)
{
	line_list *tem;
	line_list *current;

	if (head != NULL)
	{
		current = *head;
		while ((tem = current) != NULL)
		{
			current = current->next;
			free(tem);
		}
		*head = NULL;
	}
}
