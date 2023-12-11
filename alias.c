#include "shell.h"

/**
 * print_alias - add, remove or show aliases
 * @data: struct for the program's data
 * @alias: name of the alias to be printed
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int print_alias(container_of_program *data, char *alias)
{
	int i, j, len;
	char buffer[250] = {'\0'};

	if (data->custom_alias_list)
	{
		len = str_length(alias);
		for (i = 0; data->custom_alias_list[i]; i++)
		{
			if (!alias || (str_compare(data->custom_alias_list[i], alias, len)
				&&	data->custom_alias_list[i][len] == '='))
			{
				for (j = 0; data->custom_alias_list[i][j]; j++)
				{
					buffer[j] = data->custom_alias_list[i][j];
					if (data->custom_alias_list[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				buffer_add(buffer, "'");
				buffer_add(buffer, data->custom_alias_list[i] + j + 1);
				buffer_add(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * get_alias - add, remove or show aliases
 * @data: struct for the program's data
 * @name: name of the requested alias.
 * Return: zero if sucess, or other number if its declared in the arguments
 */
char *get_alias(container_of_program *data, char *name)
{
	int i, len;


	if (name == NULL || data->custom_alias_list == NULL)
		return (NULL);

	len = str_length(name);

	for (i = 0; data->custom_alias_list[i]; i++)
	{
		if (str_compare(name, data->custom_alias_list[i], len) &&
			data->custom_alias_list[i][len] == '=')
		{
			return (data->custom_alias_list[i] + len + 1);
		}
	}

	return (NULL);

}

/**
 * set_alias - add, or override alias
 * @alias_string: alias to be seted in the form (name='value')
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int set_alias(char *alias_string, container_of_program *data)
{
	int i, j;
	char buffer[250] = {'0'}, *temp = NULL;

	if (alias_string == NULL ||  data->custom_alias_list == NULL)
		return (1);

	for (i = 0; alias_string[i]; i++)
		if (alias_string[i] != '=')
			buffer[i] = alias_string[i];
		else
		{
			temp = get_alias(data, alias_string + i + 1);
			break;
		}


	for (j = 0; data->custom_alias_list[j]; j++)
		if (str_compare(buffer, data->custom_alias_list[j], i) &&
			data->custom_alias_list[j][i] == '=')
		{
			free(data->custom_alias_list[j]);
			break;
		}


	if (temp)
	{
		buffer_add(buffer, "=");
		buffer_add(buffer, temp);
		data->custom_alias_list[j] = str_duplicate(buffer);
	}
	else
		data->custom_alias_list[j] = str_duplicate(alias_string);
	return (0);
}

