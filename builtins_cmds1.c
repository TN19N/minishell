/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmds1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 09:31:41 by hnaciri-          #+#    #+#             */
/*   Updated: 2022/02/15 17:56:38 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_exit(void)
{
	printf("exit\n");
	exit(0);
}

void	ft_env(void)
{
	int	i;

	i = 0;
	while (g_data.my_env[i])
	{
		printf("%s\n", g_data.my_env[i]);
		i++;
	}
	g_data.errsv = 0;
}

void	ft_pwd(void)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	printf("%s\n", tmp);
	free(tmp);
	g_data.errsv = 0;
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
