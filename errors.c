#include "shell.h"

/**
 *_eputs -To prints an input string
 * @str: string to be printed
 *
 * Return: Value Nothing
 */
void _eputs(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_eputchar(str[j]);
		j++;
	}
}

/**
 * _eputchar - To writes the character k to stderr
 * @k: k is the character to print
 *
 * Return: Value On success 1.
 * On error, -1 is returned, and errno is set to appropriately.
 */
int _eputchar(char k)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (k == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (k != BUF_FLUSH)
		buf[i++] = k;
	return (1);
}

/**
 * _putfd -To writes the character k to a given fd
 * @k:k is the character to print
 * @fd: Is the filedescriptor to write to
 *
 * Return: Value On success 1.
 * On error, -1 is returned, and errno is set to appropriately.
 */
int _putfd(char k, int fd)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (k == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fd, buf, j);
		j = 0;
	}
	if (k != BUF_FLUSH)
		buf[j++] = k;
	return (1);
}

/**
 *_putsfd -To prints an input string
 * @str: string to be printed to
 * @fd: Is the filedescriptor to write to
 *
 * Return: Always return the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int j = 0;

	if (!str)
		return (0);
	while (*str)
	{
		j += _putfd(*str++, fd);
	}
	return (j);
}
