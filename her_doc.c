/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 12:45:01 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/16 14:40:21 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_line(int *her_pipe, t_token *token)
{
	char	*line;

	if (pipe(her_pipe) == -1)
		ft_error(NULL);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, token->next->tok))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, her_pipe[WRITE]);
		free(line);
	}
	close(her_pipe[WRITE]);
}

int	here_doc(t_mini_data *mini_data, int *her_pipe)
{
	t_token	*token;

	her_pipe = NULL;
	token = mini_data->token_list;
	while (token)
	{
		if (token->type == HERE_DOC)
		{
			if (!her_pipe)
			{
				free(her_pipe);
				her_pipe = malloc(sizeof(int) * 2);
				if (!her_pipe)
					ft_error(NULL);
			}
			dup2(g_data.save_out, STDOUT_FILENO);
			read_line(her_pipe, token);
			dup2(g_data.save_tmp_fd, STDOUT_FILENO);
		}
		token = token->next;
	}
	if (her_pipe)
		dup2(her_pipe[READ], STDIN_FILENO);
	free(her_pipe);
	return (0);
}
