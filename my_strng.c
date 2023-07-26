#include "shell.h"

/**
 * reverse_str - fun that reverses a string.
 * @s: entry string.
 * Return: no return.
 */
void reverse_str(char *s)
{
	int count = 0, a, b;
	char *str, tem;

	while (count >= 0)
	{
		if (s[count] == '\0')
			break;
		count++;
	}
	str = s;

	for (a = 0; a < (count - 1); a++)
	{
		for (b = a + 1; b > 0; b--)
		{
			tem = *(str + b);
			*(str + b) = *(str + (b - 1));
			*(str + (b - 1)) = tem;
		}
	}
}
