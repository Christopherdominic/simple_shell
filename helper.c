#include "shell.h"

/**
 * custom_free_recurrent_data - free the fields needed each loop
 * @data: struct of the program's data
 * Return: Nothing
 */
void custom_free_recurrent_data(container_of_program *data)
{
	if (data->custom_tokens)
		custom_free_array_of_pointers(data->custom_tokens);
	if (data->custom_input_line)
		free(data->custom_input_line);
	if (data->custom_command_name)
		free(data->custom_command_name);

	data->custom_input_line = NULL;
	data->custom_command_name = NULL;
	data->custom_tokens = NULL;
}

/**
 * custom_free_all_data - free all field of the data
 * @data: struct of the program's data
 * Return: Nothing
 */
void custom_free_all_data(container_of_program *data)
{
	if (data->custom_fd != 0)
	{
		if (close(data->custom_fd))
			perror(data->custom_program_name);
	}
	custom_free_recurrent_data(data);
	custom_free_array_of_pointers(data->custom_env);
	custom_free_array_of_pointers(data->custom_alias_list);
}

/**
 * custom_free_array_of_pointers - frees each pointer
 * array too
 * @array: array of pointers
 * Return: nothing
 */
void custom_free_array_of_pointers(char **array)
{
	int i;

	if (array != NULL)
	{
		for (i = 0; array[i]; i++)
			free(array[i]);

		free(array);
		array = NULL;
	}
}

