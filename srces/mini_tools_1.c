/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_tools_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:11:07 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/21 07:09:43 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_full_path(char *to_find)
{
	int		i;
	int		len;
	char	*tmp;

	i = -1;
	tmp = ft_strjoin(to_find, "=");
	len = ft_strlen(tmp);
	while (g_data.my_env[++i])
	{
		if (!ft_strncmp(g_data.my_env[i], tmp, len))
		{
			free(tmp);
			return (g_data.my_env[i] + len);
		}
	}
	free(tmp);
	return (NULL);
}

int	if_just_spaces(char *str)
{
	while (*str)
	{
		if (!is_here(*str, " \t\n\v\f\r"))
			break ;
		str++;
	}
	if (!*str)
		return (1);
	else
		return (0);
}

int	is_here(char c, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (1);
	}
	return (0);
}

void	check_if_token_full(t_token **token)
{
	if ((*token)->type != NONE)
	{
		(*token)->next = token_init((*token)->data);
		(*token)->next->last_type = (*token)->type;
		(*token) = (*token)->next;
	}
}

void	handler(int sig)
{
	int	i;

	i = 0;
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	while (i < g_data.num_childs)
	{
		kill(g_data.pid[i], SIGTERM);
		i++;
	}
	g_data.errsv = 1;
}
