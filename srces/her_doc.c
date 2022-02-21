/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 12:45:01 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/21 20:10:30 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	read_line(int *her_pipe, t_token *token)
{
	char	*line;

	if (pipe(her_pipe) == -1)
		ft_error(NULL);
	while (1)
	{
		line = readline("> ");
		printf("read line (%s)\n", line);
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

int	here_doc(t_token *token, t_mini_data *mini_data)
{
	int	her_pipe[2];

	read_line(her_pipe, token);
	if (mini_data->last_herdoc != -1)
	{
		printf("close fd=[%d] in her_doc (%s)\n", mini_data->last_herdoc, token->tok);
		close(mini_data->last_herdoc);
	}
	mini_data->last_herdoc = her_pipe[READ];
	printf("new fd=[%d] in her_doc (%s)\n", mini_data->last_herdoc, token->tok);
	return (0);
}
