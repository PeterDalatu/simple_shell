#include "shell.h"

/**
 * _myhistory -To displays the history list, one line of command, preceded
 *             with line numbers, starting at 0.
 * @info: The structure holds potential arguments and helps to maintain a
 *        constant function prototype.
 *  Return: value Always 0 succesful
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias -To sets alias to string
 * @info: the parameter struct
 * @str: the string of alias
 *
 * Return: Value Always 0 on success,and 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *q, r;
	int ret;

	q = _strchr(str, '=');
	if (!q)
		return (1);
	r = *q;
	*q = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*q = r;
	return (ret);
}

/**
 * set_alias -To sets alias to the string
 * @info: the parameter struct
 * @str: the string of alias
 *
 * Return: value always 0 on success,and 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *q;

	q = _strchr(str, '=');
	if (!q)
		return (1);
	if (!*++q)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias -To prints an alias string
 * @node: the alias of node
 *
 * Return: value always 0 on success,and 1 on error
 */
int print_alias(list_t *node)
{
	char *q = NULL, *b = NULL;

	if (node)
	{
		q = _strchr(node->str, '=');
		for (b = node->str; b <= q; b++)
			_putchar(*b);
		_putchar('\'');
		_puts(q + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias -To mimics the alias builtin of (man alias)
 * @info: The structure holds potential arguments and helps to maintain
 *         a constant function prototype.
 *  Return: Value always 0 successful
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *q = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		q = _strchr(info->argv[i], '=');
		if (q)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
