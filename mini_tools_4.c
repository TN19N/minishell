/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_tools_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 20:06:37 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/15 11:34:35 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_syntax(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_cmds)
		check_syntax_errors(&data->mini_cmds[i]);
}

void	set_her_doc_and_files(t_mini_data *mini_data, int *fd_files, int *her_pipe)
{
	here_doc(mini_data, her_pipe);
	if (fd_files)
		dup_all_files(mini_data, fd_files);
}

void	set_rederactions(t_mini_data *mini_data, int **pipes, int last_type, int index)
{
	if (mini_data->type == PIPE)
		dup2(pipes[index][WRITE], STDOUT_FILENO);
	if (last_type == PIPE)
		dup2(pipes[index - 1][READ], STDIN_FILENO);
}

void	dup_all_files(t_mini_data *mini_data, int *fd)
{
	int		i;
	t_token	*token;

	i = 0;
	while (fd[i] != -1)
		i++;
	i--;
	token = mini_data->token_list;
	while (token)
	{
		if (token->type == OUT_FILE)
			dup2(fd[i--], STDOUT_FILENO);
		else if (token->type == IN_FILE)
			dup2(fd[i--], STDIN_FILENO);
		else if (token->type == OUT_FILE_APP)
			dup2(fd[i--], STDOUT_FILENO);
		token = token->next;
	}
}
