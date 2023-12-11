#include "shell.h"

/**
 * expand_variables - expand variables
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno.
 */
void expand_variables(container_of_program *data)
{
	int i;
	int j;
	char zep[BUFFER_SIZE] = {0};
	char expansion[BUFFER_SIZE] = {'\0'};
	char *temp;

	if (data->custom_input_line == NULL)
		return;
	buffer_add(zep, data->custom_input_line);
	for (i = 0; zep[i]; i++)
		if (zep[i] == '#')
			zep[i--] = '\0';
		else if (zep[i] == '$' && zep[i + 1] == '?')
		{
			zep[i] = '\0';
			long_to_string(errno, expansion, 10);
			buffer_add(zep, expansion);
			buffer_add(zep, data->custom_input_line + i + 2);
		}
		else if (zep[i] == '$' && zep[i + 1] == '$')
		{
			zep[i] = '\0';
			long_to_string(getpid(), expansion, 10);
			buffer_add(zep, expansion);
			buffer_add(zep, data->custom_input_line + i + 2);
		}
		else if (zep[i] == '$' && (zep[i + 1] == ' ' || zep[i + 1] == '\0'))
			continue;
		else if (zep[i] == '$')
		{
			for (j = 1; zep[i + j] && zep[i + j] != ' '; j++)
				expansion[j - 1] = zep[i + j];
			temp = env_get_key(expansion, data);
			zep[i] = '\0', expansion[0] = '\0';
			buffer_add(expansion, zep + i + j);
			temp ? buffer_add(zep, temp) : 1;
			buffer_add(zep, expansion);
		}
	if (!str_compare(data->custom_input_line, zep, 0))
	{
		free(data->custom_input_line);
		data->custom_input_line = str_duplicate(zep);
	}
}

/**
 * expand_alias - expans aliases
 * @data: a pointer to a struct of the program's data
 *
 * Return: nothing, but sets errno.
 */
void expand_alias(container_of_program *data)
{
	int i;
	int j;
	int expanded = 0;
	char line[BUFFER_SIZE] = {0};
	char exp[BUFFER_SIZE] = {'\0'};
	char*temp;

	if (data->custom_input_line == NULL)
		return;

	buffer_add(line, data->custom_input_line);

	for (i = 0; line[i]; i++)
	{
		for (j = 0; line[i + j] && line[i + j] != ' '; j++)
			exp[j] = line[i + j];
		exp[j] = '\0';

		temp = get_alias(data, exp);
		if (temp)
		{
			exp[0] = '\0';
			buffer_add(exp, line + i + j);
			line[i] = '\0';
			buffer_add(line, temp);
			line[str_length(line)] = '\0';
			buffer_add(line, exp);
			expanded = 1;
		}
		break;
	}
	if (expanded)
	{
		free(data->custom_input_line);
		data->custom_input_line = str_duplicate(line);
	}
}

/**
 * buffer_add - append string at end of the buffer
 * @buffer: buffer to be filled
 * @str_to_add: string to be copied in the buffer
 * Return: nothing, but sets errno.
 */
int buffer_add(char *buffer, char *str_to_add)
{
	int len;
	int i;

	len = str_length(buffer);
	for (i = 0; str_to_add[i]; i++)
	{
		buffer[len + i] = str_to_add[i];
	}
	buffer[len + i] = '\0';
	return (len + i);
}

