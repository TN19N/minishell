/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmds2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 16:20:52 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/15 20:32:47 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check(t_token *head, char *env)
{
	char	*tmp;

	while (head)
	{
		tmp = ft_strjoin(head->tok, "=");
		if (head->type == ARGS && ft_is_valid(head->tok)
			&& !ft_strncmp(tmp, env, ft_strlen(tmp)))
		{
			free (tmp);
			return (1);
		}
		free (tmp);
		head = head->next;
	}
	return (0);
}

int	ft_is_in(char *s)
{
	int		i;
	char	*l;

	l = ft_strjoin (s, "=");
	i = -1;
	while (g_data.my_env[++i])
	{
		if (!ft_strncmp(g_data.my_env[i], l, ft_strlen (l)))
		{
			free (l);
			if (!ft_strncmp(g_data.my_env[i], "OLDPWD=", 7))
				g_data.first_pwd = 1;
			return (1);
		}
	}
	free (l);
	return (0);
}

int	ft_is_valid(char *s)
{
	int	i;

	i = 0;
	if (!ft_isalpha (s[i]))
	{
		g_data.errsv = 1;
		return (0);
	}
	while (s[++i])
	{
		if (!ft_isalnum(s[i]))
		{
			g_data.errsv = 1;
			return (0);
		}
	}
	return (1);
}

char	**alloc_new_env(t_token *head, int *tmp)
{
	char	**new_env;

	*tmp = g_data.count;
	while (head)
	{
		if (head->type == ARGS)
		{
			if(!ft_is_valid(head->tok))
			{
				ft_unset_err(head->tok);
				g_data.errsv = 1;
			}
			if (ft_is_in(head->tok))
				(*tmp)--;
		}
		head = head->next;
	}
	new_env = ft_calloc((*tmp + 1), sizeof(char *));
	if (!new_env)
		ft_error(NULL);
	return (new_env);
}
