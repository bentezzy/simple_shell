#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(ShellInfo *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = getLineInput(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->lineCountFlag = 1;
			removeComments(*buf);
			buildHistoryList(info, *buf, info->histCount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->commandBuffer = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t getInput(ShellInfo *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	shell_putchar(BUFFER_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		checkChain(info, buf, &j, i, len);
		while (j < len)
		{
			if (isChain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->commandBufferType = COMMAND_NORMAL;
		}

		*buf_p = p;
		return (stringLength(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * read_buf - reads a buffer
 * @buf: buffer
 * @info: parameter struct
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(ShellInfo *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUFFER_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * getLineInput - gets the next line of input from STDIN
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 * @info: parameter
 *
 * Return: s
 */
int getLineInput(ShellInfo *info, char **ptr, size_t *length)
{
	size_t k;
	ssize_t d = 0, s = 0;
	static char buf[READ_BUFFER_SIZE];
	static size_t bn, len;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (bn == len)
		k = len = 0;

	d = read_buf(info, buf, &len);
	if (d == -1 || (d == 0 && len == 0))
		return (-1);

	c = stringCharacter(buf + bn, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = memoryReallocate(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		stringConcatenateN(new_p, buf + bn, k - bn);
	else
		stringCopyN(new_p, buf + bn, k - bn + 1);

	s += k - bn;
	bn = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - ctrl-C
 * @sig_num: signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	shell_puts("\n");
	shell_puts("$ ");
	shell_putchar(BUFFER_FLUSH);
}
