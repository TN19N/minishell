/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmds1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 09:31:41 by hnaciri-          #+#    #+#             */
/*   Updated: 2022/02/25 13:56:55 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_error(char *tok)
{
	printf("minishell : exit: %s: numeric argument required\n", tok);
	exit(255);
}

static long long	my_atoi(char *tok)
{
	u_int64_t	num;
	int			o;
	int			i;
	int			valid;
	char		*tok_copy;

	o = 1;
	i = 0;
	num = 0;
	valid = 0;
	tok_copy = ft_strtrim(tok, " ");
	if (tok_copy[i] == '-' || tok_copy[i] == '+')
		if (tok_copy[i++] == '-')
			o = -1;
	if (atoi_part_2(&tok_copy[i], &valid, &num, o) || valid == 0)
	{
		free(tok_copy);
		exit_error(tok);
	}
	free(tok_copy);
	return (num * o);
}

void	ft_exit(t_mini_data *mini_data)
{
	t_token		*token;
	int			i;
	long long	to_return;
	int			valid;

	i = 0;
	valid = 0;
	printf("exit\n");
	token = mini_data->token_list;
	while (token)
	{
		if (token->type == ARGS)
			break ;
		token = token->next;
	}
	if (!token)
		exit (0);
	to_return = my_atoi(token->tok);
	if (number_of_types(mini_data, ARGS) > 1)
	{
		g_data.errsv = 1;
		printf("bash : exit: too many arguments\n");
	}
	else
		exit(my_atoi(token->tok) % 256);
}

void	ft_env(void)
{
	int	i;

	i = 0;
	g_data.errsv = 0;
	while (g_data.my_env[i])
	{
		printf("%s\n", g_data.my_env[i]);
		i++;
	}
}

void	ft_unset(t_mini_data *mini_data)
{
	t_token	*head;
	char	**new_env;
	int		i_and_j[2];
	int		tmp;

	i_and_j[0] = -1;
	i_and_j[1] = -1;
	tmp = 0;
	g_data.errsv = 0;
	head = grep_a_type(mini_data->token_list, CMD);
	new_env = alloc_new_env(head, &tmp);
	while (g_data.my_env[++i_and_j[0]])
		if (!ft_check(head, g_data.my_env[i_and_j[0]]))
			new_env[++i_and_j[1]] = ft_strdup(g_data.my_env[i_and_j[0]]);
	new_env[++i_and_j[1]] = NULL;
	ft_free (g_data.my_env);
	g_data.my_env = new_env;
	g_data.count = tmp;
}
