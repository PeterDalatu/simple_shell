#include "shell.h"

/**
 * _erratoi -To converts a string k to an integer
 * @k: k is the string to be converted
 * Return: Value 0 if no numbers in string, converted number otherwise
 *       -1 on error.
 */
int _erratoi(char *k)
{
	int j = 0;
	unsigned long int result = 0;

	if (*k == '+')
		k++;  /* TODO: why does this make main return 255? */
	for (j = 0;  k[j] != '\0'; j++)
	{
		if (k[j] >= '0' && k[j] <= '9')
		{
			result *= 10;
			result += (k[j] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error -To prints an error message
 * @info: the return info struct & parameter
 * @estr: the string that contains specified error type
 * Return: Value 0 if no numbers in string, converted number
 *          otherwise, -1 on error
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d -The function prints a decimal (integer) number
 *          to (base 10)
 * @input: Is the input
 * @fd: Is the filedescriptor to write to
 *
 * Return: the number of characters to be printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int j, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + current / j);
			count++;
		}
		current %= j;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number -To convert a function, a clone of atoi
 * @num: Is the number
 * @flags: Is the argument flags
 * @base: Is the base
 *
 * Return: The string
 */
char *convert_number(long int num, int flags, int base)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments -The function replaces first instance of the '#'
 *                  with '\0'
 * @buf: The address of the string to be modify
 *
 * Return: value always 0;
 */
void remove_comments(char *buf)
{
	int j;

	for (j = 0; buf[j] != '\0'; j++)
		if (buf[j] == '#' && (!j || buf[j - 1] == ' '))
		{
			buf[j] = '\0';
			break;
		}
}
