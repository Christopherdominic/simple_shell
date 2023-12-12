#include "shell.h"
/**
 * main - initialize the variables of the program
 * @argc: number of values received from the command line
 * @argv: values received from the command line
 * @env: number of values received from the command line
 * Return: zero on succes.
 */
int main(int argc, char *argv[], char *env[])
{
	container_of_program data_struct = {NULL}, *data = &data_struct;
	char *alert = "";

	custom_initialize_data(data, argc, argv, env);

	signal(SIGINT, custom_handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		alert = PROMPT_MSG;
	}
	errno = 0;
	ifo(alert, data);
	return (0);
}

/**
 * custom_handle_ctrl_c - print the prompt in a new line
 * when the signal SIGINT (ctrl + c) is send to the program
 * @UNUSED: option of the prototype
 */
void custom_handle_ctrl_c(int opr UNUSED)
{
	custom_print("\n");
	custom_print(PROMPT_MSG);
}

/**
 * custom_initialize_data - initialize the struct with the info of the program
 * @data: pointer to the structure of data
 * @argv: array of arguments pased to the program execution
 * @env: environ pased to the program execution
 * @argc: number of values received from the command line
 */
void custom_initialize_data(container_of_program *data, int argc,
		char *argv[], char **env)
{
	int j = 0;

	data->custom_program_name = argv[0];
	data->custom_input_line = NULL;
	data->custom_command_name = NULL;
	data->custom_exec_counter = 0;

	if (argc == 1)
		data->custom_fd = STDIN_FILENO;
	else
	{
		data->custom_fd = open(argv[1], O_RDONLY);
		if (data->custom_fd == -1)
		{
			custom_printe(data->custom_program_name);
			custom_printe(": 0: Can't open ");
			custom_printe(argv[1]);
			custom_printe("\n");
			exit(127);
		}
	}
	data->custom_tokens = NULL;
	data->custom_env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[j]; j++)
		{
			data->custom_env[j] = custom_str_duplicate(env[j]);
		}
	}
	data->custom_env[j] = NULL;
	env = data->custom_env;

	data->custom_alias_list = malloc(sizeof(char *) * 20);
	for (j = 0; j < 20; j++)
	{
		data->custom_alias_list[j] = NULL;
	}
}
/**
 * ifo - its a infinite loop that shows the prompt
 * @prompt: prompt to be printed
 * @data: its a infinite loop that shows the prompt
 */
void ifo(char *prompt, container_of_program *data)
{
	int error = 0, string_len = 0;

	while (++(data->custom_exec_counter))
	{
		custom_print(prompt);
		error = string_len = custom_getline(data);

		if (error == EOF)
		{
			custom_free_all_data(data);
			exit(errno);
		}
		if (string_len >= 1)
		{
			custom_expand_alias(data);
			custom_expand_variables(data);
			custom_tokenize(data);
			if (data->custom_tokens[0])
			{
				error = custom_execute(data);
				if (error != 0)
					custom_print_error(error, data);
			}
			custom_free_recurrent_data(data);
		}
	}
}

