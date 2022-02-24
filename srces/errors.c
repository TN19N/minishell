/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:11:28 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/24 14:42:31 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_syntax_errors(t_mini_data *mini_data)
{
	if (!*mini_data->all_cmd || if_just_spaces(mini_data->all_cmd))
	{
		if (mini_data->type == PIPE)
			ft_putendl_fd("minishell: syntax error near \
unexpected token `|\'", 2);
		g_data.errsv = 258;
		free_all(mini_data->data, NULL, 0);
		return (1);
	}
	return (0);
}

void	no_home_for_cd(void)
{
	ft_putendl_fd("minishell: cd: HOME not set", 2);
	g_data.errsv = 1;
}

void	ft_unset_export_err(char *s, int i)
{
	if (i == 1)
		ft_putstr_fd("minishell: unset: `", 2);
	else
		ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd (s, 2);
	ft_putendl_fd ("': not a valid identifier", 2);
}

void	ft_error(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	if (!str)
		perror(NULL);
	else
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ", 2);
		if (g_data.errsv == 127)
			ft_putendl_fd("command not found", 2);
		else if (g_data.errsv == 1)
			ft_putendl_fd("No such file or directory", 2);
		else if (g_data.errsv == 126)
			ft_putendl_fd("Permission denied", 2);
		exit(g_data.errsv);
	}
	exit(EXIT_FAILURE);
}
