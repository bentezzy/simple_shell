#include "shell.h"

/**
 * get_length - Get the leng of a number.
 * @n: an int num.
 * Return: Lenghth of a number.
 */
int get_length(int n)
{
	unsigned int b;
	int lenghth = 1;

	if (n < 0)
	{
		lenghth++;
		b = n * -1;
	}
	else
	{
		b = n;
	}
	while (b > 9)
	{
		lenghth++;
		b = b / 10;
	}

	return (lenghth);
}
/**
 * my_itoa - function converts int to string.
 * @n: an int num
 * Return: String.
 */
char *my_itoa(int n)
{
	unsigned int b;
	int lenghth = get_length(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (lenghth + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + lenghth) = '\0';

	if (n < 0)
	{
		b = n * -1;
		buffer[0] = '-';
	}
	else
	{
		b = n;
	}

	lenghth--;
	do {
		*(buffer + lenghth) = (b % 10) + '0';
		b = b / 10;
		lenghth--;
	}
	while (b > 0)
		;
	return (buffer);
}

/**
 * _atoi - converts a string to an integer.
 * @s: input string.
 * Return: integer.
 */
int _atoi(char *s)
{
	unsigned int count = 0, size = 0, oi = 0, pn = 1, v = 1, c;

	while (*(s + count) != '\0')
	{
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;

		if (*(s + count) == '-')
			pn *= -1;

		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			if (size > 0)
				v *= 10;
			size++;
		}
		count++;
	}

	for (c = count - size; c < count; c++)
	{
		oi = oi + ((*(s + c) - 48) * v);
		v /= 10;
	}
	return (oi * pn);
}
