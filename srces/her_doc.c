/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 12:45:01 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/24 12:50:33 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	here_doc(int *her_pipe, t_token *token)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, token->next->tok))
		{
			free(line);
			close(her_pipe[WRITE]);
			break ;
		}
		ft_putendl_fd(line, her_pipe[WRITE]);
		free(line);
	}
	close(her_pipe[WRITE]);
	close(her_pipe[READ]);
	exit(EXIT_SUCCESS);
}

int	fork_childe(t_data *data, int i, t_token *token, int *pipe_fd)
{
	int	returned;

	returned = 0;
	if (data->mini_cmds[i].last_herdoc != -1)
		close(pipe_fd[READ]);
	if (pipe(pipe_fd) == -1)
		ft_error(NULL);
	data->here_doc_to_kill = fork();
	if (data->here_doc_to_kill == -1)
		ft_error(NULL);
	else if (data->here_doc_to_kill == 0)
	{
		signal(SIGINT, SIG_DFL);
		here_doc(pipe_fd, token);
	}
	else
		if (wait(&returned) == -1)
			ft_error(NULL);
	return (returned);
}

int	check_returned(t_data *data, int i, int returned, int *pipe_fd)
{
	if (WIFSIGNALED(returned))
	{
		close(pipe_fd[WRITE]);
		close(pipe_fd[READ]);
		return (1);
	}
	else
	{
		data->mini_cmds[i].last_herdoc = pipe_fd[READ];
		close(pipe_fd[WRITE]);
		return (0);
	}
}	

int	creat_child_for_heredoc(t_data *data)
{
	int		returned;
	int		i;
	t_token	*token;
	int		pipe_fd[2];

	i = 0;
	while (i < data->num_cmds)
	{
		data->mini_cmds[i].last_herdoc = -1;
		token = data->mini_cmds[i].token_list;
		while (token)
		{
			if (token->type == HERE_DOC)
			{
				returned = fork_childe(data, i, token, pipe_fd);
				data->here_doc_to_kill = -1;
				if (check_returned(data, i, returned, pipe_fd))
					return (1);
			}
			token = token->next;
		}
		i++;
	}
	return (0);
}
