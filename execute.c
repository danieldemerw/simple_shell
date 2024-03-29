/* execute function */
#include "shell.h"

/**
 * new_process - create a new process
 * @args: array of strings that contain command
 *
 * Return: -1 if success, 0 otherwise
 */
int new_process(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
	{
		perror("Error: failed to fork child process\n");
	}
	else if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("./shell");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		do {
			if (waitpid(pid, &status, WUNTRACED) == -1)
			{
				perror("error");
			}
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (-1);
}

/**
 * get_function - selects correct function to perform the task
 * operator passed as argument to the program
 * **args
 * Return: pointer to function corresponding to built in function
 */
int (*get_function(char *s))(char **args)
{
	builtin list[] = {
		{"cd", shell_cd},
		{"help", shell_help},
		{"exit", shell_exit},
		{"env", shell_env},
		{"setenv", shell_setenv},
		{"unsetenv", shell_unsetenv},
		{NULL, NULL}
	};
	int i = 0;

	while (list[i].builtin_str != NULL && _strcmp(s, list[i].builtin_str) != 0)
	{
		i++;
	}

	return (list[i].builtin_func);
}

/**
 * execute - maps if command is a process or builtin
 *
 *
 * Return: function or process if successful or else -1
 */
int execute(char **args)
{
	if (args[0] == NULL)
	{
		return (-1);
	}
	if (get_function(args[0]) == NULL)
	{
		return (new_process(args));
	}
	return (get_function(args[0])(args));
}
/* it is good */
