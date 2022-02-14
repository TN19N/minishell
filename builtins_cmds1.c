/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmds1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 09:31:41 by hnaciri-          #+#    #+#             */
/*   Updated: 2022/02/14 17:21:46 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **a)
{
	int	i;

	i = -1;
	while (a[++i])
		free(a[i]);
	free(a);
}

void	ft_exit(void)
{
	printf("exit\n");
	exit(0);
}

void	ft_env(void)
{
	int	i;

	i = -1;
	while (data.my_env[++i])
		printf("%s\n", data.my_env[i]);
}

void	ft_pwd(void)
{
	int	i;

	i = -1;
	while (data.my_env[++i])
		if (!ft_strncmp(data.my_env[i], "PWD=", 4))
			printf("%s\n", data.my_env[i] + 4);
}

void	ft_unset(t_mini_data *mini_data)
{
	t_token	*head;
	char	**new_env;
	int		i_and_j[2];
	int		tmp;
	int		check_if_err;

	i_and_j[0] = -1;
	i_and_j[1] = -1;
	tmp = 0;
	check_if_err = 0;
	head = grep_a_type(mini_data->token_list, CMD);
	new_env = alloc_new_env(head, &tmp, &check_if_err);
	while (data.my_env[++i_and_j[0]])
		if (!ft_check(head, data.my_env[i_and_j[0]]))
			new_env[++i_and_j[1]] = ft_strdup(data.my_env[i_and_j[0]]);
	new_env[++i_and_j[1]] = NULL;
	ft_free (data.my_env);
	data.my_env = new_env;
	data.count = tmp;
	if (check_if_err != 0)
		exit(1);
}