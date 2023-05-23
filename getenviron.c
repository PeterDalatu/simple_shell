#include "shell.h"

/**
 * get_environ -To returns the string array copy of our environ
 * @info: The structure holds potential arguments and helps to maintain
 *        a constant function prototype.
 * Return: Value always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv -To remove an environment variable
 * @info: The structure holds potential arguments and helps to maintain
 *       a constant function prototype.
 * @var: Is the string env var property
 *
 *  Return:values 1 on delete, 0 otherwise
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *k;

	if (!node || !var)
		return (0);

	while (node)
	{
		k = starts_with(node->str, var);
		if (k && *k == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv -To Initialize a new environment variable,
 *             or to modify an existing one
 * @info: The structure holds potential arguments and helps to maintain
 *       a constant function prototype.
 * @value:Is the string env var value
 * @var: Is the string env var property
 *
 *  Return: Value always 0 successful
 */
int _setenv(info_t *info, char *value, char *var)
{
	char *buf = NULL;
	list_t *node;
	char *k;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node)
	{
		k = starts_with(node->str, var);
		if (k && *k == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}
