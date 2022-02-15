/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_tools_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:20:38 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/15 12:45:53 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	number_of_types(t_mini_data *mini_data, int type)
{
	int		count;
	t_token	*token;

	count = 0;
	token = mini_data->token_list;
	while (token)
	{
		if (token->type == type)
			count++;
		token = token->next;
	}
	return (count);
}

void	alloc_pipes(int count, int ***pipes)
{
	int	i;

	*pipes = malloc(sizeof(int *) * count);
	if (!*pipes)
		ft_error(NULL);
	i = -1;
	while (++i < count)
	{
		(*pipes)[i] = malloc(sizeof(int) * 2);
		if (!(*pipes)[i])
			ft_error(NULL);
	}
	count--;
	while (count >= 0)
	{
		if (pipe((*pipes)[count--]) == -1)
			ft_error(NULL);
	}
}

int	get_pipes(t_data *data, int ***pipes)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	*pipes = NULL;
	while (++i < data->num_cmds)
	{
		if (data->mini_cmds[i].type == PIPE)
			count++;
	}
	if (count != 0)
		alloc_pipes(count, pipes);
	return (count);
}

void	creat_files(t_token *token, int *fd, int *num_fd)
{
	int	error;

	error = 0;
	if (token->type == OUT_FILE)
	{
		fd[*num_fd] = open(token->tok, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		error = 1;
	}
	else if (token->type == IN_FILE)
	{
		fd[*num_fd] = open(token->tok, O_RDONLY | O_EXCL);
		error = 1;
	}
	else if (token->type == OUT_FILE_APP)
	{
		fd[*num_fd] = open(token->tok, O_WRONLY | O_CREAT | O_APPEND, 0644);
		error = 1;
	}
	if (error == 1 && fd[(*num_fd)--] == -1)
	{
		g_data.errsv = 1;
		ft_error(token->tok);
	}
}

int	wait_for_child(t_data *data, int i)
{
	int	returned;

	waitpid(data->pid[i], &returned, 0);
	if (WIFSIGNALED(returned))
		data->errsv = 130;
	else
		data->errsv = WEXITSTATUS(returned);
	if (data->mini_cmds[i].type == ORLOG && returned == 0)
		return (1);
	else if (data->mini_cmds[i].type == ANDLOG && returned != 0)
		return (1);
	return (0);
}
