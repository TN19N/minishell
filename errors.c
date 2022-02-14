/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaciri- <hnaciri-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 18:21:24 by mannouao          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/02/14 17:22:24 by mannouao         ###   ########.fr       */
=======
/*   Updated: 2022/02/14 14:05:57 by hnaciri-         ###   ########.fr       */
>>>>>>> bebae7780885a6bc7f7933897317bbd13ff9f4de
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_syntax_errors(t_mini_data *mini_data)
{
	if (!*mini_data->all_cmd || if_just_spaces(mini_data->all_cmd))
	{
		if (mini_data->type == PIPE)
			ft_putendl_fd("minishell: syntax error near \
unexpected token `|\'", 2);
		else if (mini_data->type == ANDLOG)
			ft_putendl_fd("minishell: syntax error near \
unexpected token `&&\'", 2);
		else if (mini_data->type == ORLOG)
			ft_putendl_fd("minishell: syntax error near \
unexpected token `||\'", 2);
		data.errsv = 258;
		free_all(mini_data->data, NULL, 0);
		get_cmd_line();
	}
}

void	ft_unset_err (char *s)
{
	ft_putstr_fd("minishell: unset: `", 2);
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
		if (data.errsv == 127)
			ft_putendl_fd("command not found", 2);
		else if (data.errsv == 1)
			ft_putendl_fd("No such file or directory", 2);
		else if (data.errsv == 126)
			ft_putendl_fd("Permission denied", 2);
		exit(data.errsv);
	}
	exit(EXIT_FAILURE);
}
