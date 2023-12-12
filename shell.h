#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

#include "macros.h"

/************* STRUCTURES **************/

/**
 * struct info- struct for the program's data
 * @program_name: the name of the executable
 * @input_line: pointer to the input read for _getline
 * @command_name: pointer to the first command typed by the user
 * @exec_counter: number of excecuted comands
 * @file_descriptor: file descriptor to the input of commands
 * @tokens: pointer to array of tokenized input
 * @env: copy of the environ
 * @alias_list: array of pointers with aliases.
 */
typedef struct info
{
	char *custom_program_name;
	char *custom_input_line;
	char *custom_command_name;
	int custom_exec_counter;
	int custom_fd;
	char **custom_tokens;
	char **custom_env;
	char **custom_alias_list;
} container_of_program;

/**
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(container_of_program *data);
} builtins;


void custom_initialize_data(container_of_program *data, int arc, char *argv[], char **env);

void ifo(char *prompt, container_of_program *data);

void custom_handle_ctrl_c(int opr UNUSED);

int custom_getline(container_of_program *data);

int custom_check_logic_ops(char *array_commands[], int i, char array_operators[]);

void custom_expand_variables(container_of_program *data);

void custom_expand_alias(container_of_program *data);

int custom_buffer_add(char *buffer, char *str_to_add);

void custom_tokenize(container_of_program *data);

char *custom_strtok(char *line, char *delim);

int custom_execute(container_of_program *data);

int custom_builtins_list(container_of_program *data);

char **custom_tokenize_path(container_of_program *data);

int custom_find_program(container_of_program *data);

void custom_free_array_of_pointers(char **directories);

void custom_free_recurrent_data(container_of_program *data);

void custom_free_all_data(container_of_program *data);

int custom_builtin_exit(container_of_program *data);

int custom_builtin_cd(container_of_program *data);

int custom_set_work_directory(container_of_program *data, char *new_dir);

int custom_builtin_help(container_of_program *data);

int custom_builtin_alias(container_of_program *data);

int custom_builtin_env(container_of_program *data);

int custom_builtin_set_env(container_of_program *data);

int custom_builtin_unset_env(container_of_program *data);

char *custom_env_get_key(char *name, container_of_program *data);

int custom_env_set_key(char *key, char *value, container_of_program *data);

int custom_env_remove_key(char *key, container_of_program *data);

void custom_print_environ(container_of_program *data);

int custom_print(char *string);

int custom_printe(char *string);

int custom_print_error(int errorcode, container_of_program *data);

int custom_str_length(char *string);

char *custom_str_duplicate(char *string);

int custom_str_compare(char *string1, char *string2, int number);

char *custom_str_concat(char *string1, char *string2);

void custom_str_reverse(char *string);

void  custom_long_to_string(long number, char *string, int base);

int  custom_atoi(char *s);

int  custom_count_characters(char *string, char *character);

int custom_print_alias(container_of_program *data, char *alias);

char *custom_get_alias(container_of_program *data, char *alias);

int custom_set_alias(char *alias_string, container_of_program *data);

#endif /* SHELL_H */

