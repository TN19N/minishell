/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_tools_6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 10:47:32 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/27 15:24:21 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handl_singl_things(int *i, char *cmd_line, int tmp, char c)
{
	int	b = 0;

	if (!cmd_line[*i + 1])
		b = 1;
	while (!b && cmd_line[tmp] != c && cmd_line[tmp])
		tmp++;
	if (!b && !cmd_line[tmp])
	{
		*i = tmp - 1;
		b = 1;
	}
	if (b == 1)
	{
		printf("We dont that here !!!; (RELANCH MINISHELL -->)\n");
		exit(42);
	}
	return (0);
}

static void	handle_specile_k(t_token *token)
{
	int		len_tk;
	int		count_dollar;
	int		i;

	if (!token->next)
		return ;
	count_dollar = 0;
	len_tk = ft_strlen(token->tok);
	if (len_tk == 0 || token->linker == 0)
		return ;
	if (token->type != WORD || token->tok[len_tk - 1] != '$')
		return ;
	if (len_tk > 1)
	{
		i = 1;
		while (token->tok[len_tk - i] && token->tok[len_tk - i] == '$')
				i++;
		if (!((i - 1) % 2))
			return ;
	}
	handle_specile_k2(token, token->next, len_tk);
}

int	update_my_tokens(t_mini_data *mini_cmd)
{
	int		first_cmd;
	t_token	*token;

	first_cmd = 0;
	token = mini_cmd->token_list;
	while (token)
	{
		handle_specile_k(token);
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
