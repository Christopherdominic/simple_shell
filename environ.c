#include "shell.h"

/**
 * env_get_key - gets the value of an environment variable
 * @key: the environment variable of interest
 * @data: struct of the program's data
 * Return: a pointer to the value of the variable or NULL if it doesn't exist
 */
char *env_get_key(char *key, container_of_program *data)
{
	int i, key_length = 0;

	/* validate the arguments */
	if (key == NULL || data->custom_env == NULL)
		return (NULL);

	/* obtains the leng of the variable requested */
	key_length = str_length(key);

	for (i = 0; data->custom_env[i]; i++)
	{/* Iterates through the environ and check for coincidence of the vame */
		if (str_compare(key, data->custom_env[i], key_length) &&
		 data->custom_env[i][key_length] == '=')
		{/* returns the value of the key NAME=  when find it*/
			return (data->custom_env[i] + key_length + 1);
		}
	}
	/* returns NULL if did not find it */
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
	int i, key_length = 0, is_new_key = 1;

	/* validate the arguments */
	if (key == NULL || value == NULL || data->custom_env == NULL)
		return (1);

	/* obtains the leng of the variable requested */
	key_length = str_length(key);

	for (i = 0; data->custom_env[i]; i++)
	{/* Iterates through the environ and check for coincidence of the vame */
		if (str_compare(key, data->custom_env[i], key_length) &&
		 data->custom_env[i][key_length] == '=')
		{/* If key already exists */
			is_new_key = 0;
			/* free the entire variable, it is new created below */
			free(data->custom_env[i]);
			break;
		}
	}
	/* make an string of the form key=value */
	data->custom_env[i] = str_concat(str_duplicate(key), "=");
	data->custom_env[i] = str_concat(data->custom_env[i], value);

	if (is_new_key)
	{/* if the variable is new, it is create at end of actual list and we need*/
	/* to put the NULL value in the next position */
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
	int i, key_length = 0;

	/* validate the arguments */
	if (key == NULL || data->custom_env == NULL)
		return (0);

	/* obtains the leng of the variable requested */
	key_length = str_length(key);

	for (i = 0; data->custom_env[i]; i++)
	{/* iterates through the environ and checks for coincidences */
		if (str_compare(key, data->custom_env[i], key_length) &&
		 data->custom_env[i][key_length] == '=')
		{/* if key already exists, remove them */
			free(data->custom_env[i]);

			/* move the others keys one position down */
			i++;
			for (; data->custom_env[i]; i++)
			{
				data->custom_env[i - 1] = data->custom_env[i];
			}
			/* put the NULL value at the new end of the list */
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
	int j;

	for (j = 0; data->custom_env[j]; j++)
	{
		_print(data->custom_env[j]);
		_print("\n");
	}
}

