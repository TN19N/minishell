/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_tools_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:11:07 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/14 18:11:50 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "minishell.h"

char	*get_full_path(char *to_find)
{
	int		i;
	int		len;
	char	*tmp;

	i = -1;
	tmp = ft_strjoin(to_find, "=");
	len = ft_strlen(tmp);
	while (data.my_env[++i])
	{
		if (!ft_strncmp(data.my_env[i], tmp, len))
		{
			free(tmp);
			return (data.my_env[i] + len);
		}
	}
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

void	check_if_token_full(t_token **token, int *last_type)
{
	if ((*token)->type != NONE)
	{
		last_type[0] = (*token)->type;
		(*token)->next = token_init((*token)->data);
		(*token) = (*token)->next;
	}
}

void	handler(int sig)
{
	int i;

	i = 0;
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	while (i < data.num_childs)
	{
		kill(data.pid[i], SIGKILL);
		i++;
	}
	data.errsv = 1;
}
