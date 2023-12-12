#include "shell.h"

/**
 * custom_print - writes a array of chars in the standar output
 * @string: pointer to the array of chars
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int custom_print(char *string)
{
	return (write(STDOUT_FILENO, string, custom_str_length(string)));
}
/**
 * custom_printe - writes a array of chars in the standar error
 * @string: pointer to the array of chars
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int custom_printe(char *string)
{
	return (write(STDERR_FILENO, string, custom_str_length(string)));
}

/**
 * custom_print_error - writes a array of chars in the standart error
 * @data: a pointer to the program's data'
 * @errorcode: error code to print
 * Return: the number of bytes writed or .
 * On error, -1 is returned, and errno is set appropriately.
 */
int custom_print_error(int errorcode, container_of_program *data)
{
	char chris_string[10] = {'\0'};

	custom_long_to_string((long) data->custom_exec_counter, chris_string, 10);

	if (errorcode == 2 || errorcode == 3)
	{
		custom_printe(data->custom_program_name);
		custom_printe(": ");
		custom_printe(chris_string);
		custom_printe(": ");
		custom_printe(data->custom_tokens[0]);
		if (errorcode == 2)
			custom_printe(": Illegal number: ");
		else
			custom_printe(": can't cd to ");
		custom_printe(data->custom_tokens[1]);
		custom_printe("\n");
	}
	else if (errorcode == 127)
	{
		custom_printe(data->custom_program_name);
		custom_printe(": ");
		custom_printe(chris_string);
		custom_printe(": ");
		custom_printe(data->custom_command_name);
		custom_printe(": not found\n");
	}
	else if (errorcode == 126)
	{
		custom_printe(data->custom_program_name);
		custom_printe(": ");
		custom_printe(chris_string);
		custom_printe(": ");
		custom_printe(data->custom_command_name);
		custom_printe(": Permission denied\n");
	}
	return (0);
}

