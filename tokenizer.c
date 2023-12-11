#include "shell.h"
/**
 * tokenize - this function separate the string using a designed delimiter
 * @data: a pointer to the program's data
 * Return: an array of the different parts of the string
 */
void tokenize(container_of_program *data)
{
	char *del = " \t";
	int i; 
	int j;
	int count = 2;
	int len;

	len = str_length(data->custom_input_line);
	if (len)
	{
		if (data->custom_input_line[len - 1] == '\n')
			data->custom_input_line[len - 1] = '\0';
	}

	for (i = 0; data->custom_input_line[i]; i++)
	{
		for (j = 0; del[j]; j++)
		{
			if (data->custom_input_line[i] == del[j])
				count++;
		}
	}

	data->custom_tokens = malloc(count * sizeof(char *));
	if (data->custom_tokens == NULL)
	{
		perror(data->custom_program_name);
		exit(errno);
	}
	i = 0;
	data->custom_tokens[i] = str_duplicate(_strtok(data->custom_input_line, del));
	data->custom_command_name = str_duplicate(data->custom_tokens[0]);
	while (data->custom_tokens[i++])
	{
		data->custom_tokens[i] = str_duplicate(_strtok(NULL, del));
	}
}

