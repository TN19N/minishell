/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_tools_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 20:06:37 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/21 15:05:57 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_syntax(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_cmds)
		check_syntax_errors(&data->mini_cmds[i]);
}

void	set_hd_and_f(t_mini_data *mini_data, int *fd_files)
{
	t_token	*token;
	int		i;

	i = 0;
	token = mini_data->token_list;
	while (token)
	{
		if (mini_data->last_herdoc != -1 && token->type == HERE_DOC)
			dup2(mini_data->last_herdoc, STDIN_FILENO);
		else if (token->type == OUT_FILE || \
		token->type == IN_FILE || token->type == OUT_FILE_APP)
			dup_all_files(token, fd_files, &i);
		token = token->next;
	}
}

void	close_p(t_mini_data *mini_data, int **pipes, int last_type, int index)
{
	int	i;

	i = 0;
	if (mini_data->type == PIPE || last_type == PIPE)
	{
		while (i < g_data.num_cmds - 1)
		{
			if (mini_data->type == PIPE && i != index)
				close(pipes[i][WRITE]);
			else if (mini_data->type != PIPE)
				close(pipes[i][WRITE]);
			if (last_type == PIPE && i != index - 1)
				close(pipes[i][READ]);
			else if (last_type != PIPE)
				close(pipes[i][READ]);
			i++;
		}
	}
}

void	set_reder(t_mini_data *mini_data, int **pipes, int last_type, int index)
{
	close_p(mini_data, pipes, last_type, index);
	if (mini_data->type == PIPE)
		dup2(pipes[index][WRITE], STDOUT_FILENO);
	if (last_type == PIPE)
		dup2(pipes[index - 1][READ], STDIN_FILENO);
}

void	dup_all_files(t_token *token, int *fd, int *i)
{
	if (token->type == OUT_FILE)
		dup2(fd[(*i)++], STDOUT_FILENO);
	else if (token->type == IN_FILE)
		dup2(fd[(*i)++], STDIN_FILENO);
	else if (token->type == OUT_FILE_APP)
		dup2(fd[(*i)++], STDOUT_FILENO);
}