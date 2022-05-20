#include "main.h"

/**
 * exec_shell - gets input and turns it into cmds
 * @av: the argument vector of the main function
 *
 * Return: a char pointer of the commands
 */
void exec_shell(char **av)
{
	char **cmds, *cmd_line, line[BUFSZ] = {0};
	ssize_t nread = 0;
	int currIndex = 0;

	print_prompt();
	nread = _getline(line, BUFSZ);
	if (nread == -1)
		exit(0);	/* EOF (Ctrl+D) captured */
	lst_ret = 0;
	while ((cmd_line = _strtok(line, "\n", &currIndex)) != NULL)
	{
		cmds = makeCmds(cmd_line);
		free(cmd_line);
		if (cmds == NULL)
		{
			perror("Error: failed to create commands");
			exec_shell(av);
		}
		if (_strcmp(cmds[0], "exit") == 0)
		{
			free_entire_arr(cmds);
			exit(lst_ret);
		}
		exec_cmds(av, cmds);
		free_entire_arr(cmds);
	}
}
