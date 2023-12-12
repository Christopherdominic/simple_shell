#include "shell.h"

/**
 * custom_print_alias - add, remove or show aliases
 * @data: struct for the program's data
 * @alias: name of the alias to be printed
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int custom_print_alias(container_of_program *data, char *alias)
{
	int i, j, len;
	char buffer[250] = {'\0'};

	if (data->custom_alias_list)
	{
		len = custom_str_length(alias);
		for (i = 0; data->custom_alias_list[i]; i++)
		{
			if (!alias || (custom_str_compare(data->custom_alias_list[i], alias, len)
				&&	data->custom_alias_list[i][len] == '='))
			{
				for (j = 0; data->custom_alias_list[i][j]; j++)
				{
					buffer[j] = data->custom_alias_list[i][j];
					if (data->custom_alias_list[i][j] == '=')
						break;
				}
				buffer[j + 1] = '\0';
				custom_buffer_add(buffer, "'");
				custom_buffer_add(buffer, data->custom_alias_list[i] + j + 1);
				custom_buffer_add(buffer, "'\n");
				custom_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * custom_get_alias - add, remove or show aliases
 * @data: struct for the program's data
 * @name: name of the requested alias.
 * Return: zero if sucess, or other number if its declared in the arguments
 */
char *custom_get_alias(container_of_program *data, char *name)
{
	int i, len;


	if (name == NULL || data->custom_alias_list == NULL)
		return (NULL);

	len = custom_str_length(name);

	for (i = 0; data->custom_alias_list[i]; i++)
	{
		if (custom_str_compare(name, data->custom_alias_list[i], len) &&
			data->custom_alias_list[i][len] == '=')
		{
			return (data->custom_alias_list[i] + len + 1);
		}
	}

	return (NULL);

}

/**
 * custom_set_alias - add, or override alias
 * @alias_string: alias to be seted in the form (name='value')
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int custom_set_alias(char *alias_string, container_of_program *data)
{
	int i, j;
	char buffer[250] = {'0'}, *temp = NULL;

		return (1);

	for (i = 0; alias_string[i]; i++)
		if (alias_string[i] != '=')
			buffer[i] = alias_string[i];
		else
		{
			temp = custom_get_alias(data, alias_string + i + 1);
			break;
		}


	for (j = 0; data->custom_alias_list[j]; j++)
		if (custom_str_compare(buffer, data->custom_alias_list[j], i) &&
			data->custom_alias_list[j][i] == '=')
		{
			free(data->custom_alias_list[j]);
			break;
		}


	if (temp)
	{
		custom_buffer_add(buffer, "=");
		custom_buffer_add(buffer, temp);
		data->custom_alias_list[j] = custom_str_duplicate(buffer);
	}
	else
		data->custom_alias_list[j] = custom_str_duplicate(alias_string);
	return (0);
}

