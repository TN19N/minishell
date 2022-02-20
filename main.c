/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 09:19:46 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/19 16:51:43 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child(char **args, char *cmd_path, int *pipes, int mode)
{
	if (mode == WRITE)
	{
		dup2(pipes[WRITE], STDOUT_FILENO);
		close (pipes[READ]);
	}
	else if (mode == READ)
	{
		dup2(pipes[READ], STDIN_FILENO);
	}
	execve(cmd_path, args, NULL);
}

int main()
{
		int pid1;
		int pid2;
		int i;
		int	pipes[2];
		char *args[4];
		args [0] = "head";
		args[1] = "-c";
		args [2] = "10";
		args [3] = NULL;
		char *cmd_path = "/usr/bin/head";

		char *args2[3];
		args2 [0] = "cat";
		args2[1] = "/dev/random";
		args2 [2] = NULL;
		char *cmd_path2 = "/bin/cat";

		i = 0;
		pipe(pipes);
		pid1 = fork();
		if (pid1 == 0)
			child(args2, cmd_path2, pipes, WRITE);
		close(pipes[WRITE]);
		pid2 = fork();
		if (pid2 == 0)
			child(args, cmd_path, pipes, READ);
		close(pipes[WRITE]);
		close(pipes[READ]);
		i = 0;
		waitpid (pid1, 0, 0);
		waitpid (pid2, 0, 0);
}