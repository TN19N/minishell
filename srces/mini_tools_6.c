/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_tools_6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 10:47:32 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/23 09:24:51 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handl_singl_things(int *i, char *cmd_line, int tmp, char c)
{
	if (!cmd_line[*i + 1])
		return (1);
	while (cmd_line[tmp] != c && cmd_line[tmp])
		tmp++;
	if (!cmd_line[tmp])
	{
		*i = tmp - 1;
		return (1);
	}
	return (0);
}

void	update_my_tokens(t_mini_data *mini_cmd)
{
	int		first_cmd;
	t_token	*token;

	first_cmd = 0;
	token = mini_cmd->token_list;
	while (token)
	{
		if (token->type != SINGLE_QUOTE)
			handl_env_ver(&token->tok);
		token = token->next;
	}
	combine_the_words(mini_cmd->token_list);
	token = mini_cmd->token_list;
	while (token)
	{
		init_tokens(&token, &first_cmd);
		token = token->next;
	}
}

void	active_all_heredoc(t_data *data)
{
	t_token	*token;
	int		i;

	i = 0;
	while (i < data->num_cmds)
	{
		data->mini_cmds[i].last_herdoc = -1;
		token = data->mini_cmds[i].token_list;
		while (token)
		{
			if (token->type == HERE_DOC)
				here_doc(token, &data->mini_cmds[i]);
			token = token->next;
		}
		i++;
	}
}
