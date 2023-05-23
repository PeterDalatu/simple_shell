#include "shell.h"
/**
 * is_chain - to test if current char in buffer is a chain delimeter
 * @info: a parameter struct
 * @buf: a char buffer
 * @q: the address of current position in buf
 *
 * Return: value 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *q)
{
	size_t j = *q;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of a command */
	{
		buf[j] = 0; /* replace the semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*q = j;
	return (1);
}
/**
 * check_chain - the checks to continue chaining based on last status
 * @info: a parameter struct
 * @buf: a char buffer
 * @q: the address of current position in buf
 * @i: the starting position in buf
 * @len: the length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *q, size_t i, size_t len)
{
	size_t j = *q;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	*q = j;
}
/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *q;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		q = _strchr(node->str, '=');
		if (!q)
			return (0);
		q = _strdup(q + 1);
		if (!q)
			return (0);
		info->argv[0] = q;
	}
	return (1);
}
/**
 * replace_vars - To replaces vars in the tokenized string
 * @info: a parameter struct
 *
 * Return: value 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int i = 0;

	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;
		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));
	}
	return (0);
}
/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
