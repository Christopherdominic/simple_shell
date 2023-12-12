#include "shell.h"

int custom_check_file(char *full_path);

/**
 * custom_find_program - find a program in path
 * @data: a pointer to the program's data
 * Return: 0 if success, errcode otherwise
 */

int custom_find_program(container_of_program *data)
{
	int i = 0, chris_code = 0;
	char **director;

	if (!data->custom_command_name)
		return (2);


	if (data->custom_command_name[0] == '/' ||
			data->custom_command_name[0] == '.')
		return (custom_check_file(data->custom_command_name));

	free(data->custom_tokens[0]);
	data->custom_tokens[0] = custom_str_concat(custom_str_duplicate("/"),
			data->custom_command_name);
	if (!data->custom_tokens[0])
		return (2);

	director = custom_tokenize_path(data);

	if (!director || !director[0])
	{
		errno = 127;
		return (127);
	}
	for (i = 0; director[i]; i++)
	{
		director[i] = custom_str_concat(director[i], data->custom_tokens[0]);
		chris_code = custom_check_file(director[i]);
		if (chris_code == 0 || chris_code == 126)
		{
			errno = 0;
			free(data->custom_tokens[0]);
			data->custom_tokens[0] = custom_str_duplicate(director[i]);
			custom_free_array_of_pointers(director);
			return (chris_code);
		}
	}
	free(data->custom_tokens[0]);
	data->custom_tokens[0] = NULL;
	custom_free_array_of_pointers(director);
	return (chris_code);
}

/**
 * custom_tokenize_path - tokenize the path in directories
 * @data: a pointer to the program's data
 * Return: array of path directories
 */

char **custom_tokenize_path(container_of_program *data)
{
	int i = 0;
	int c = 2;
	char **tokens = NULL;
	char *PATH;


	PATH = custom_env_get_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		return (NULL);
	}

	PATH = custom_str_duplicate(PATH);


	for (i = 0; PATH[i]; i++)
	{
		if (PATH[i] == ':')
			c++;
	}


	tokens = malloc(sizeof(char *) * c);


	i = 0;
	tokens[i] = custom_str_duplicate(custom_strtok(PATH, ":"));
	while (tokens[i++])
	{
		tokens[i] = custom_str_duplicate(custom_strtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);

}

/**
 * custom_check_file - checks if exists a file, if it is not a dairectory and
 * if it has excecution permisions for permisions.
 * @full_path: pointer to the full file name
 * Return: 0 on success, or error code if it exists.
 */

int custom_check_file(char *full_path)
{
	struct stat ch;

	if (stat(full_path, &ch) != -1)
	{
		if (S_ISDIR(ch.st_mode) ||  access(full_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}

	errno = 127;
	return (127);
}

