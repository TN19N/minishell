/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_tools_5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 10:25:14 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/18 16:55:39 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*open_files(t_mini_data *mini_data)
{
	int		num_fd;
	int		*fd;
	t_token	*token;

	num_fd = number_of_types(mini_data, OUT_FILE);
	num_fd += number_of_types(mini_data, IN_FILE);
	num_fd += number_of_types(mini_data, OUT_FILE_APP);
	if (num_fd == 0)
		return (NULL);
	fd = malloc(sizeof(int) * (num_fd + 1));
	if (!fd)
		ft_error(NULL);
	fd[num_fd--] = -1;
	token = mini_data->token_list;
	while (token)
	{
		creat_files(token, fd, &num_fd);
		token = token->next;
	}
	return (fd);
}

void	init_to_start(t_data *data, int	***pipes, int *num_pipes, int *l_type)
{
	*num_pipes = get_pipes(data, pipes);
	*l_type = LASTONE;
	data->pid = malloc(sizeof(int) * data->num_cmds);
	if (!data->pid)
		ft_error(NULL);
}

void	mix_tokens(t_token **token)
{
	char	*tmp;
	t_token	*tmp_token;

	tmp_token = (*token)->next->next;
	tmp = (*token)->tok;
	(*token)->tok = ft_strjoin((*token)->tok, (*token)->next->tok);
	free(tmp);
	free((*token)->next->tok);
	free((*token)->next);
	(*token)->next = tmp_token;
}

void	combine_the_words(t_token *token)
{
	while (token)
	{
		if (token->linker && token->next)
		{
			while (token->next && token->next->linker)
				mix_tokens(&token);
			if (token->next)
				mix_tokens(&token);
			token->linker = 0;
		}
		else
			token = token->next;
	}
}
