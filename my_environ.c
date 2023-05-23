#include "shell.h"

/**
 * _myenv -To prints the current environment
 * @info: The structure holds potential arguments and helps to maintain
 *        a constant function prototype.
 * Return:Value always 0 successful
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv -To gets the value of an environ variable
 * @info: The structure holds potential arguments and helps to maintain
 *        a constant function prototype.
 * @name:The env var name
 *
 * Return: Always the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *q;

	while (node)
	{
		q = starts_with(node->str, name);
		if (q && *q)
			return (q);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv -To Initialize a new environ variable,
 *             or to modify an existing one
 * @info: The structure holds potential arguments and helps to maintain
 *        a constant function prototype.
 *  Return: Value always 0 successful
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv -To remove an environment variable
 * @info: The structure holds potential arguments and helps to maintain
 *        a constant function prototype.
 *  Return: value always 0 successful
 */
int _myunsetenv(info_t *info)
{
	int j;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= info->argc; j++)
		_unsetenv(info, info->argv[j]);

	return (0);
}

/**
 * populate_env_list -To populates an env linked list
 * @info: The structure holds potential arguments and helps to maintain
 *        a constant function prototype.
 * Return: Value always 0 successful
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		add_node_end(&node, environ[j], 0);
	info->env = node;
	return (0);
}
