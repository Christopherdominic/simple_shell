#include "shell.h"

/**
 * custom_builtin_exit - exit of the program with the status
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int custom_builtin_exit(container_of_program *data)
{
	int i;

	if (data->custom_tokens[1] != NULL)
	{
		for (i = 0; data->custom_tokens[1][i]; i++)
			if ((data->custom_tokens[1][i] < '0' || data->custom_tokens[1][i] > '9')
				&& data->custom_tokens[1][i] != '+')
			{
				errno = 2;
				return (2);
			}
		errno = custom_atoi(data->custom_tokens[1]);
	}
	custom_free_all_data(data);
	exit(errno);
}

/**
 * custom_builtin_cd - change the current directory
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int custom_builtin_cd(container_of_program *data)
{
	char *directory_home = custom_env_get_key("HOME", data),
	     *directory_old = NULL;
	char old_directory[128] = {0};
	int error = 0;

	if (data->custom_tokens[1])
	{
		if (custom_str_compare(data->custom_tokens[1], "-", 0))
		{
			directory_old = custom_env_get_key("OLDPWD", data);
			if (directory_old)
				error = custom_set_work_directory(data, directory_old);
			custom_print(custom_env_get_key("PWD", data));
			custom_print("\n");

			return (error);
		}
		else
		{
			return (custom_set_work_directory(data, data->custom_tokens[1]));
		}
	}
	else
	{
		if (!directory_home)
			directory_home = getcwd(old_directory, 128);

		return (custom_set_work_directory(data, directory_home));
	}
	return (0);
}

/**
 * custom_set_work_directory - set the work directory
 * @data: struct for the program's data
 * @new_dir: path to be set as work directory
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int custom_set_work_directory(container_of_program *data, char *new_dir)
{
	char old_directory[128] = {0};
	int error = 0;

	getcwd(old_directory, 128);

	if (!custom_str_compare(old_directory, new_dir, 0))
	{
		error = chdir(new_dir);
		if (error == -1)
		{
			errno = 2;
			return (3);
		}
		custom_env_set_key("PWD", new_dir, data);
	}
	custom_env_set_key("OLDPWD", old_directory, data);
	return (0);
}

/**
 * custom_builtin_help - shows the environment where the shell runs
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int custom_builtin_help(container_of_program *data)
{
	int i, length = 0;
	char *chriswork[6] = {NULL};

	chriswork[0] = HELP_MSG;


	if (data->custom_tokens[1] == NULL)
	{
		custom_print(chriswork[0] + 6);
		return (1);
	}
	if (data->custom_tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->custom_command_name);
		return (5);
	}
	chriswork[1] = HELP_EXIT_MSG;
	chriswork[2] = HELP_ENV_MSG;
	chriswork[3] = HELP_SETENV_MSG;
	chriswork[4] = HELP_UNSETENV_MSG;
	chriswork[5] = HELP_CD_MSG;

	for (i = 0; chriswork[i]; i++)
	{
		length = custom_str_length(data->custom_tokens[1]);
		if (custom_str_compare(data->custom_tokens[1], chriswork[i], length))
		{
			custom_print(chriswork[i] + length + 1);
			return (1);
		}
	}

	errno = EINVAL;
	perror(data->custom_command_name);
	return (0);
}

/**
 * custom_builtin_alias - add, remove or show aliases
 * @data: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int custom_builtin_alias(container_of_program *data)
{
	int i = 0;


	if (data->custom_tokens[1] == NULL)
		return (custom_print_alias(data, NULL));

	while (data->custom_tokens[++i])
	{
		if (custom_count_characters(data->custom_tokens[i], "="))
			custom_set_alias(data->custom_tokens[i], data);
		else
			custom_print_alias(data, data->custom_tokens[i]);
	}

	return (0);
}

