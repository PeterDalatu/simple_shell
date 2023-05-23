#include "shell.h"

/**
 * _strncpy - Copies a string
 * @dest: Destination string
 * @src: Source string
 * @n: Number of characters to be copied
 * Return: Pointer to the destination string
 */
char *_strncpy(char *dest, const char *src, int n)
{
	int j;

	for (j = 0; j < n && src[j] != '\0'; j++)
		dest[j] = src[j];

	for (; j < n; j++)
		dest[j] = '\0';

	return (dest);
}

/**
 * _strncat - Concatenates two strings
 * @dest: Destination string
 * @src: Source string
 * @n: Maximum number of characters to be appended
 * Return: Pointer to the destination string
 */
char *_strncat(char *dest, const char *src, int n)
{
	int i, j;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (j = 0; j < n && src[j] != '\0'; j++)
		dest[i + j] = src[j];

	dest[i + j] = '\0';

	return (dest);
}

/**
 * _strchr - Locates a character in a string
 * @str: String to be parsed
 * @c: Character to look for
 * Return: Pointer to the first occurrence of the character
 *         or NULL if not found
 */
char *_strchr(char *str, char c)
{
	while (*str != '\0')
	{
		if (*str == c)
			return (str);

		str++;
	}

	return (NULL);
}
