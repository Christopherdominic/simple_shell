#include "shell.h"

/**
* _getline - read one line from the prompt.
* @data: struct for the program's data
*
* Return: reading counting bytes.
*/
int custom_getline(container_of_program *data)
{
	char buffer[BUFFER_SIZE] = {'\0'};
	static char *array_size[10] = {NULL};
	static char array_operator[10] = {'\0'};
	ssize_t bytes_read, i = 0;


	if (!array_size[0] || (array_operator[0] == '&' && errno != 0) ||
		(array_operator[0] == '|' && errno == 0))
	{
	
		for (i = 0; array_size[i]; i++)
		{
			free(array_size[i]);
			array_size[i] = NULL;
		}

		
		bytes_read = read(data->custom_fd, &buffer, BUFFER_SIZE - 1);
		if (bytes_read == 0)
			return (-1);

		
		i = 0;
		do {
			array_size[i] = custom_str_duplicate(custom_strtok(i ? NULL : buffer, "\n;"));

			i = custom_check_logic_ops(array_size, i, array_operator);
		} while (array_size[i++]);
	}

	data->custom_input_line = array_size[0];
	for (i = 0; array_size[i]; i++)
	{
		array_size[i] = array_size[i + 1];
		array_operator[i] = array_operator[i + 1];
	}

	return (custom_str_length(data->custom_input_line));
}


/**
* custom_check_logic_ops - checks and split for && and || operators
* @array_commands: array of the commands.
* @i: index in the array_commands to be checked
* @array_operators: array of the logical operators for each previous command
*
* Return: index of the last command in the array_commands.
*/
int custom_check_logic_ops(char *array_commands[], int i, char array_operators[])
{
	char *temp = NULL;
	int j;

	for (j = 0; array_commands[i] != NULL  && array_commands[i][j]; j++)
	{
		if (array_commands[i][j] == '&' && array_commands[i][j + 1] == '&')
		{

			temp = array_commands[i];
			array_commands[i][j] = '\0';
			array_commands[i] = custom_str_duplicate(array_commands[i]);
			array_commands[i + 1] = custom_str_duplicate(temp + j + 2);
			i++;
			array_operators[i] = '&';
			free(temp);
			j = 0;
		}
		if (array_commands[i][j] == '|' && array_commands[i][j + 1] == '|')
		{

			temp = array_commands[i];
			array_commands[i][j] = '\0';
			array_commands[i] = custom_str_duplicate(array_commands[i]);
			array_commands[i + 1] = custom_str_duplicate(temp + j + 2);
			i++;
			array_operators[i] = '|';
			free(temp);
			j = 0;
		}
	}
	return (i);
}

