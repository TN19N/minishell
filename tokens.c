/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 17:05:25 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/15 13:20:59 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_init(t_data *data)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		ft_error(NULL);
	token->next = NULL;
	token->type = NONE;
	token->tok = NULL;
	token->data = data;
	return (token);
}

void	quotes(t_token **token, char *cmd_line, int *i, int *last_type)
{
	int		j;
	char	c;

	j = *i + 1;
	c = cmd_line[*i];
	check_if_token_full(token, last_type);
	while (cmd_line[++*i])
	{
		if (cmd_line[*i] == c)
		{
			(*token)->tok = ft_substr(cmd_line, j, *i - j);
			if (c == '\"')
				init_tokens(token, last_type, DOUBLE_QUOTE);
			else if (c == '\'')
				init_tokens(token, last_type, SINGLE_QUOTE);
			*i += 2;
			break ;
		}
	}
}

void	redirecters(t_token **token, char *cmd_line, int *i, int *last_type)
{
	check_if_token_full(token, last_type);
	if (cmd_line[*i] == '<' && cmd_line[*i + 1] == '<')
	{
		(*token)->tok = ft_substr(cmd_line, *i, 2);
		*i += 1;
		init_tokens(token, last_type, HERE_DOC);
	}
	else if (cmd_line[*i] == '<')
	{
		(*token)->tok = ft_substr(cmd_line, *i, 1);
		init_tokens(token, last_type, REDIRECT_IN);
	}
	else if (cmd_line[*i] == '>' && cmd_line[*i + 1] == '>')
	{
		(*token)->tok = ft_substr(cmd_line, *i, 2);
		*i += 1;
		(*token)->type = REDIRECT_OUT_APP;
		init_tokens(token, last_type, REDIRECT_OUT_APP);
	}
	else if (cmd_line[*i] == '>')
	{
		(*token)->tok = ft_substr(cmd_line, *i, 1);
		init_tokens(token, last_type, REDIRECT_OUT);
	}
}

void	words(t_token **token, char *cmd_line, int *i, int *last_type)
{
	int	j;

	j = *i;
	if (!cmd_line[*i])
		return ;
	check_if_token_full(token, last_type);
	while (!is_here(cmd_line[*i], " <>\'\"") && cmd_line[*i])
		*i += 1;
	*i -= 1;
	(*token)->tok = ft_substr(cmd_line, j, (*i - j) + 1);
	init_tokens(token, last_type, WORD);
}

void	get_tokens(char *all_cmd, t_mini_data *mini_cmd)
{
	t_token	*token;
	int		i;
	int		j;
	int		last_type[2];

	i = -1;
	j = 0;
	mini_cmd->token_list = token_init(mini_cmd->data);
	token = mini_cmd->token_list;
	last_type[0] = token->type;
	last_type[1] = 0;
	while (all_cmd[++i])
	{
		if (is_here(all_cmd[i], "\"\'"))
			quotes(&token, all_cmd, &i, last_type);
		else if (is_here(all_cmd[i], "<>"))
			redirecters(&token, all_cmd, &i, last_type);
		else if (!is_here(all_cmd[i], " \t\n\v\f\r"))
			words(&token, all_cmd, &i, last_type);
	}
}
