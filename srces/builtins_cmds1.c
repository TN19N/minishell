/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmds1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 09:31:41 by hnaciri-          #+#    #+#             */
/*   Updated: 2022/02/21 09:19:14 by mannouao         ###   ########.fr       */
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
	unsigned long long	num;
	int					o;
	int					i;

	o = 42;
	i = -1;
	while (tok[i] == ' ')
		i++;
	if (tok[i] == '-' || tok[i] == '+')
		if (tok[i++] == '-')
			o = -1;
	while (tok[i] >= '0' && tok[i] <= '9')
	{
		o = 1;
		num = (num * 10) + (tok[i] - '0');
		if (num > __LONG_MAX__ && o == 1)
			exit_error(tok);
		else if (num > (unsigned long long)__LONG_MAX__ + \
		(unsigned long long)1 && o == -1)
			exit_error(tok);
		i++;
	}
	if (o == 42 || (tok[i] != '\0' && tok[i] != ' '))
		exit_error(tok);
	return (num * o);
}

void	ft_exit(t_mini_data *mini_data)
{
	t_token		*token;
	int			i;
	long long	to_return;

	i = 0;
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
