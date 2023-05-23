#include "shell.h"

/**
 **_strncpy - To copy a string
 *@dest: Is the destination string to be copied to
 *@src: Is the source string
 *@a: Isthe amount of characters to be copied
 *Return: Always the concatenated string
 */
char *_strncpy(char *dest, char *src, int a)
{
	int j, k;
	char *s = dest;

	j = 0;
	while (src[j] != '\0' && j < a - 1)
	{
		dest[j] = src[j];
		j++;
	}
	if (j < a)
	{
		k = j;
		while (k < a)
		{
			dest[k] = '\0';
			k++;
		}
	}
	return (s);
}

/**
 **_strncat -To concatenates two strings
 *@dest: Is the first string
 *@src: Is the second string
 *@a: Is the amount of bytes to be maximally used
 *Return: Always the concatenated string
 */
char *_strncat(char *dest, char *src, int a)
{
	int j, k;
	char *s = dest;

	j = 0;
	k = 0;
	while (dest[j] != '\0')
		j++;
	while (src[k] != '\0' && k < a)
	{
		dest[j] = src[k];
		j++;
		k++;
	}
	if (k < a)
		dest[j] = '\0';
	return (s);
}

/**
 **_strchr - to locates a character in a string
 *@u: is the string to be parsed
 *@v: is the character to look for
 *Return: the value (u) a pointer to the memory area u
 */
char *_strchr(char *u, char v)
{
	do {
		if (*u == v)
			return (u);
	} while (*u++ != '\0');

	return (NULL);
}
