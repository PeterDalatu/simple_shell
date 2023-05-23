#include "shell.h"

/**
 * interactive - To returns true if shell is at interactive mode
 * @info: Information of the struct address
 *
 * Return: Value 1 if at interactive mode,value 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - To checks if character is a delimeter
 * @k: k is the char to check
 * @delim: is the delimeter string
 * Return: Value 1 if true,value 0 if false
 */
int is_delim(char k, char *delim)
{
	while (*delim)
		if (*delim++ == k)
			return (1);
	return (0);
}

/**
 *_isalpha - To checks for alphabetic character
 *@u: u is the character to input
 *Return: Value 1 if u is alphabetic, 0 otherwise
 */

int _isalpha(int u)
{
	if ((u >= 'a' && u <= 'z') || (u >= 'A' && u <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - To converts a string to an integer
 *@p: p is the string to be converted
 *Return: Value 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *p)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  p[i] != '\0' && flag != 2; i++)
	{
		if (p[i] == '-')
			sign *= -1;

		if (p[i] >= '0' && p[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (p[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
