#include "shell.h"

/**
 * env_get_key - gets the value of an environment variable
 * @key: the environment variable of interest
 * @data: struct of the program's data
 * Return: a pointer to the value of the variable or NULL if it doesn't exist
 */
char *env_get_key(char *key, container_of_program *data)
{
	int j, length = 0;


	if (key == NULL || data->custom_env == NULL)
		return (NULL);


	length = str_length(key);

	for (j = 0; data->custom_env[j]; j++)
	{
		if (str_compare(key, data->custom_env[j], length) &&
		 data->custom_env[j][length] == '=')
		{
			return (data->custom_env[j] + length + 1);
		}
	}

	return (NULL);
}

/**
 * env_set_key - overwrite the value of the environment variable
 * or create it if does not exist.
 * @key: name of the variable to set
 * @value: new value
 * @data: struct of the program's data
 * Return: 1 if the parameters are NULL, 2 if there is an erroror 0 if sucess.
 */

int env_set_key(char *key, char *value, container_of_program *data)
{
	int i, length = 0, keyed = 1;


	if (key == NULL || value == NULL || data->custom_env == NULL)
		return (1);


	length = str_length(key);

	for (i = 0; data->custom_env[i]; i++)
	{
		if (str_compare(key, data->custom_env[i], length) &&
		 data->custom_env[i][length] == '=')
		{
			keyed = 0;
		
			free(data->custom_env[i]);
			break;
		}
	}

	data->custom_env[i] = str_concat(str_duplicate(key), "=");
	data->custom_env[i] = str_concat(data->custom_env[i], value);

	if (keyed)
	{
		data->custom_env[i + 1] = NULL;
	}
	return (0);
}

/**
 * env_remove_key - remove a key from the environment
 * @key: the key to remove
 * @data: the sructure of the program's data
 * Return: 1 if the key was removed, 0 if the key does not exist;
 */
int env_remove_key(char *key, container_of_program *data)
{
	int i, length = 0;


	if (key == NULL || data->custom_env == NULL)
		return (0);

	length = str_length(key);

	for (i = 0; data->custom_env[i]; i++)
	{
		if (str_compare(key, data->custom_env[i], length) &&
		 data->custom_env[i][length] == '=')
		{
			free(data->custom_env[i]);

		
			i++;
			for (; data->custom_env[i]; i++)
			{
				data->custom_env[i - 1] = data->custom_env[i];
			}

			data->custom_env[i - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * print_environ - prints the current environ
 * @data: struct for the program's data
 * Return: nothing
 */
void print_environ(container_of_program *data)
{
	int i;

	for (i = 0; data->custom_env[i]; i++)
	{
		custom_print(data->custom_env[i]);
		custom_print("\n");
	}
}

