/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 12:45:01 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/20 15:23:30 by mannouao         ###   ########.fr       */
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
			close(her_pipe[WRITE]);
			break ;
		}
		ft_putendl_fd(line, her_pipe[WRITE]);
		free(line);
	}
	close(her_pipe[WRITE]);
}

int	here_doc(t_token *token)
{
	int	her_pipe[2];

	dup2(g_data.save_out, STDOUT_FILENO);
	dup2(g_data.save_in, STDIN_FILENO);
	read_line(her_pipe, token);
	dup2(g_data.fack_out, STDOUT_FILENO);
	dup2(g_data.fack_in, STDIN_FILENO);
	fprintf(stderr, "dup input with pipe her_pipe[READ] in cmd (%s)", token->tok);
	dup2(her_pipe[READ], STDIN_FILENO);
	g_data.fack_in = her_pipe[READ];
	return (0);
}
