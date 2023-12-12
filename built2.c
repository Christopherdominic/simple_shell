#include "shell.h"

/**
 * custom_builtins_list - search for match and execute the associate builtin
 * @data: struct for the program's data
 * Return: Returns the return of the function executed is there is a match,
 * otherwise returns -1.
 **/
int custom_builtins_list(container_of_program *data)
{
	int christo;
	builtins options[] = {
		{"exit", custom_builtin_exit},
		{"help", custom_builtin_help},
		{"cd", custom_builtin_cd},
		{"alias", custom_builtin_alias},
		{"env", custom_builtin_env},
		{"setenv", custom_builtin_set_env},
		{"unsetenv", custom_builtin_unset_env},
		{NULL, NULL}
	};

	for (christo = 0; options[christo].builtin != NULL; christo++)
	{

		if (custom_str_compare(options[christo].builtin, data->custom_command_name, 0))
		{

			return (options[christo].function(data));
		}

	}
	return (-1);
}

