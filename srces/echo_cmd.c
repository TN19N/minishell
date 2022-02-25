/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:45:57 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/25 16:22:17 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_n_function(t_token *token)
{
	int	i;

	i = 0;
	if (!token)
		return (0);
	if (token->type == ARGS)
	{
		if (token->tok[i] != '-' || !token->tok[i + 1])
			return (0);
		while (token->tok[++i])
			if (token->tok[i] != 'n')
				return (0);
		return (1);
	}
	return (0);
}

void	start_printing(t_token *token, int *n, int *first)
{
	while (token)
	{
		if (token->type == ARGS)
		{
			if (!ft_n_function(token))
				break ;
			token = token->next;
			*n = -1;
		}
		else
			token = token->next;
	}
	while (token)
	{
		if (token->type == ARGS)
		{
			if (*first)
				write(STDOUT_FILENO, " ", 1);
			else
				*first = 1;
			ft_putstr_fd(token->tok, STDOUT_FILENO);
		}
		token = token->next;
	}
}

void	ft_echo(t_mini_data *mini_data)
{
	int		n;
	int		first;
	t_token	*token;

	first = 0;
	g_data.errsv = 0;
	token = grep_a_type(mini_data->token_list, CMD);
	if (token->next)
		token = token->next;
	else
		return ;
	n = 1;
	start_printing(token, &n, &first);
	if (n == 1)
		printf ("\n");
}
