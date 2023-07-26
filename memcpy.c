#include "shell.h"

/**
 * _memcpy - copies info between void pointers.
 * @n_ptr: destination pointer.
 * @ptr: source pointer.
 * @size: size of the end pointer.
 *
 * Return: no return.
 */
void _memcpy(void *n_ptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_n_ptr = (char *)n_ptr;
	unsigned int a;

	for (a = 0; a < size; a++)
		char_n_ptr[a] = char_ptr[a];
}

/**
 * _realloc - reallocates a memory block.
 * @ptr: pointer to the old memory allocated.
 * @old_size: size in bytes of the allocated space of pointer.
 * @new_size: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *n_ptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	n_ptr = malloc(new_size);
	if (n_ptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcpy(n_ptr, ptr, new_size);
	else
		_memcpy(n_ptr, ptr, old_size);

	free(ptr);
	return (n_ptr);
}

/**
 * _realloc_d - reallocates memory block of a double pointer.
 * @ptr: double pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
char **_realloc_d(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **n_ptr;
	unsigned int a;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	n_ptr = malloc(sizeof(char *) * new_size);
	if (n_ptr == NULL)
		return (NULL);

	for (a = 0; a < old_size; a++)
		n_ptr[a] = ptr[a];

	free(ptr);

	return (n_ptr);
}
