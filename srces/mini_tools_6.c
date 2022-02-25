/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_tools_6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 10:47:32 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/25 13:54:04 by mannouao         ###   ########.fr       */
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

int	update_my_tokens(t_mini_data *mini_cmd)
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
		if (init_tokens(&token, &first_cmd))
			return (1);
		token = token->next;
	}
	return (0);
}

void	handler2(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_data.errsv = 1;
}

int	atoi_part_2(char *tok_copy, int *valid, u_int64_t *num, int o)
{
	int	i;

	i = 0;
	while (tok_copy[i] >= '0' && tok_copy[i] <= '9')
	{
		*valid = 1;
		*num = (*num * 10) + (tok_copy[i] - '0');
		if (*num > __LONG_MAX__ && o == 1)
			return (1);
		else if (*num > (u_int64_t)__LONG_MAX__ + \
		(u_int64_t)1 && o == -1)
			return (1);
		i++;
	}
	if (tok_copy[i])
		return (1);
	return (0);
}
