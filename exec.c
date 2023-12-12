#include "shell.h"
/**
 * execute - execute a command with its entire path variables.
 * @data: a pointer to the program's data
 * Return: If sucess returns zero, otherwise, return -1.
 */
int execute(container_of_program *data)
{
	int heg = 0; 
	int status;
	pid_t pidd;

	/* check for program in built ins */
	heg = custom_builtins_list(data);
	if (heg != -1)/* if program was found in built ins */
		return (heg);

	/* check for program file system */
	heg = find_program(data);
	if (heg)
	{/* if program not found */
		return (heg);
	}
	else
	{/* if program was found */
		pidd = fork(); /* create a child process */
		if (pidd == -1)
		{ /* if the fork call failed */
			perror(data->custom_command_name);
			exit(EXIT_FAILURE);
		}
		if (pidd == 0)
		{/* I am the child process, I execute the program*/
			heg = execve(data->custom_tokens[0], data->custom_tokens, data->custom_env);
			if (heg == -1) /* if error when execve*/
				perror(data->custom_command_name), exit(EXIT_FAILURE);
		}
		else
		{/* I am the father, I wait and check the exit status of the child */
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}

