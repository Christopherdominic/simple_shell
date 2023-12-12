#include "shell.h"

/**
 * custom_builtin_env - shows the environment where the shell runs
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int custom_builtin_env(container_of_program *data)
{
	int i;
	char cpname[50] = {'\0'};
	char *var_copy = NULL;


	if (data->custom_tokens[1] == NULL)
		custom_print_environ(data);
	else
	{
		for (i = 0; data->custom_tokens[1][i]; i++)
		{
			if (data->custom_tokens[1][i] == '=')
			{
				var_copy = custom_str_duplicate(custom_env_get_key(cpname, data));
				if (var_copy != NULL)
					custom_env_set_key(cpname, data->custom_tokens[1] + i + 1, data);


				custom_print_environ(data);
				if (custom_env_get_key(cpname, data) == NULL)
				{
					custom_print(data->custom_tokens[1]);
					custom_print("\n");
				}
				else
				{
					custom_env_set_key(cpname, var_copy, data);
					free(var_copy);
				}
				return (0);
			}
			cpname[i] = data->custom_tokens[1][i];
		}
		errno = 2;
		perror(data->custom_command_name);
		errno = 127;
	}
	return (0);
}

/**
 * custom_builtin_set_env - building the set env
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int custom_builtin_set_env(container_of_program *data)
{

	if (data->custom_tokens[1] == NULL || data->custom_tokens[2] == NULL)
		return (0);
	if (data->custom_tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->custom_command_name);
		return (5);
	}

	custom_env_set_key(data->custom_tokens[1], data->custom_tokens[2], data);

	return (0);
}

/**
 * custom_builtin_unset_env - build the set env
 * @data: struct for the program's data'
 * Return: ..
 */
int custom_builtin_unset_env(container_of_program *data)
{

	if (data->custom_tokens[1] == NULL)
		return (0);
	if (data->custom_tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->custom_command_name);
		return (5);
	}
	custom_env_remove_key(data->custom_tokens[1], data);

	return (0);
}

