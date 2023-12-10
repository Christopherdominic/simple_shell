#include "shell.h"
/**
 * main - initialize the variables of the program
 * @argc: number of values received from the command line
 * @argv: values received from the command line
 * @custom_env: number of values received from the command line
 * Return: zero on succes.
 */
int main(int argc, char *argv[], char *custom_env[])
{
	container_of_program data_struct = {NULL}, *data = &data_struct;
	char *prompt = "";

	initialize_data(data, argc, argv, custom_env);

	signal(SIGINT, handle_ctrl_c);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{/* We are in the terminal, interactive mode */
		errno = 2;/*???????*/
		prompt = PROMPT_MSG;
	}
	errno = 0;
	ifo(prompt, data);
	return (0);
}

/**
 * handle_ctrl_c - print the prompt in a new line
 * when the signal SIGINT (ctrl + c) is send to the program
 * @UNUSED: option of the prototype
 */
void handle_ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * initialize_data - inicialize the struct with the info of the program
 * @data: pointer to the structure of data
 * @argv: array of arguments pased to the program execution
 * @env: environ pased to the program execution
 * @argc: number of values received from the command line
 */
void initialize_data(data_of_program *data, int argc, char *argv[], char **env)
{
	int i = 0;

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
			_printe(data->custom_program_name);
			_printe(": 0: Can't open ");
			_printe(argv[1]);
			_printe("\n");
			exit(127);
		}
	}
	data->custom_tokens = NULL;
	data->custom_env = malloc(sizeof(char *) * 50);
	if (custom_env)
	{
		for (; custom_env[i]; i++)
		{
			data->custom_env[i] = str_duplicate(custom_env[i]);
		}
	}
	data->custom_env[i] = NULL;
	env = data->custom_env;

	data->custom_alias_list = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data->custom_alias_list[i] = NULL;
	}
}
/**
 * ifo - its a infinite loop that shows the prompt
 * @prompt: prompt to be printed
 * @data: its a infinite loop that shows the prompt
 */
void ifo(char *prompt, container_of_program *data)
{
	int error_code = 0, string_len = 0;

	while (++(data->custom_exec_counter))
	{
		_print(prompt);
		error_code = string_len = custom_getline(data);

		if (error_code == EOF)
		{
			free_all_data(data);
			exit(errno); /* if EOF is the fisrt Char of string, exit*/
		}
		if (string_len >= 1)
		{
			expand_alias(data);
			expand_variables(data);
			tokenize(data);
			if (data->custom_tokens[0])
			{ /* if a text is given to prompt, execute */
				error_code = execute(data);
				if (error_code != 0)
					_print_error(error_code, data);
			}
			free_recurrent_data(data);
		}
	}
}

