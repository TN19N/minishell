/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 14:45:57 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/16 15:56:39 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_n_function(t_token *token)
{
	int	i;

	i = 0;
	if (token->type == ARGS)
	{
		if (token->tok[i] != '-')
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
	while (ft_n_function(token))
	{
		token = token->next;
		*n = -1;
	}
	while (token)
	{
		if (token->type == ARGS)
		{
			if (*first)
				printf(" ");
			else
				*first = 1;
			printf ("%s", token->tok);
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
	token = grep_a_type(mini_data->token_list, CMD);
	if (mini_data->token_list->next)
		token = mini_data->token_list->next;
	else
		return ;
	n = 1;
	start_printing(token, &n, &first);
	if (n == 1)
		printf ("\n");
}
