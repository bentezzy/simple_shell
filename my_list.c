#include "shell.h"

/**
 * _rvar_node - fun that adds a var at the end
 * of a r_var list.
 * @head:  linked list head .
 * @l_var: length of the variable.
 * @val: value of the variable.
 * @l_val: length of the value.
 * Return: address of the head.
 */
r_var *_rvar_node(r_var **head, int l_var, char *val, int l_val)
{
	r_var *fresh, *tem;

	fresh = malloc(sizeof(r_var));
	if (fresh == NULL)
		return (NULL);

	fresh->len_var = l_var;
	fresh->val = val;
	fresh->len_val = l_val;

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
 * free_rvar_list - frees a r_var list
 * @head: linked list head.
 * Return: no return.
 */
void free_rvar_list(r_var **head)
{
	r_var *tem;
	r_var *current;

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
