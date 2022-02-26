/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 12:45:01 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/26 10:35:32 by mannouao         ###   ########.fr       */
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
	int	pid;

	returned = 0;
	if (data->mini_cmds[i].last_herdoc != -1)
		close(pipe_fd[READ]);
	if (pipe(pipe_fd) == -1)
		ft_error(NULL);
	pid = fork();
	if (pid == -1)
		ft_error(NULL);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		here_doc(pipe_fd, token);
	}
	else
		if (waitpid(pid, &returned, 0) == -1)
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
				if (check_returned(data, i, returned, pipe_fd))
					return (1);
			}
			token = token->next;
		}
		i++;
	}
	return (0);
}

void	handle_specile_k2(t_token *token, t_token *n_token, int len_tk)
{
	char	*tmp_tok;

	if (n_token->type == DOUBLE_QUOTE || n_token->type == SINGLE_QUOTE)
	{
		tmp_tok = token->tok;
		token->tok = ft_substr(token->tok, 0, len_tk - 1);
		free(tmp_tok);
	}
}
