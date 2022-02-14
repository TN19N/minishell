/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:15:35 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/14 07:32:54 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_spliter(t_data *data, int *i)
{
	if (data->cmd_line[*i] == '|')
	{
		if (data->cmd_line[*i + 1] == '|')
		{
			*i += 1;
			data->num_cmds++;
		}
		else
			data->num_cmds++;
	}
	else if (data->cmd_line[*i] == '&')
	{
		if (data->cmd_line[*i + 1] == '&')
		{
			*i += 1;
			data->num_cmds++;
		}
	}
}

void	get_number_of_cmds(t_data *data)
{
	int	i;
	int	ignore[2];

	i = -1;
	data->num_cmds = 1;
	ignore[0] = 1;
	ignore[1] = 1;
	while (data->cmd_line[++i])
	{
		if (data->cmd_line[i] == '\"' && ignore[1] == 1)
			ignore[0] *= -1;
		else if (data->cmd_line[i] == '\'' && ignore[0] == 1)
			ignore[1] *= -1;
		if (ignore[1] + ignore[0] == 2)
			if (is_here(data->cmd_line[i], "|&"))
				count_spliter(data, &i);
	}
}

void	split_spliter(t_mini_data *mini_cmds, int *i, int *j, t_data *data)
{
	mini_cmds->data = data;
	mini_cmds->token_list = NULL;
	if (data->cmd_line[*i] == '|')
	{
		if (data->cmd_line[*i + 1] == '|')
		{
			mini_cmds->all_cmd = ft_substr(data->cmd_line, *j, (*i - *j));
			mini_cmds->type = ORLOG;
			*i += 1;
			*j = *i + 1;
		}
		else
		{
			mini_cmds->all_cmd = ft_substr(data->cmd_line, *j, (*i - *j));
			mini_cmds->type = PIPE;
			*j = *i + 1;
		}
	}
	else if (data->cmd_line[*i] == '&' && data->cmd_line[*i + 1] == '&')
	{
		mini_cmds->all_cmd = ft_substr(data->cmd_line, *j, (*i - *j));
		mini_cmds->type = ANDLOG;
		*i += 1;
		*j = *i + 1;
	}
}

void	init_last_cmd(t_data *data, int index, int j, int i)
{
	data->mini_cmds[index].all_cmd = NULL;
	data->mini_cmds[index].data = data;
	data->mini_cmds[index].all_cmd = ft_substr(data->cmd_line, j, (j - i));
	data->mini_cmds[index].type = LASTONE;
}

void	get_mini_cmds(t_data *data)
{
	int	i;
	int	ignore[2];
	int	index;
	int	j;

	i = -1;
	j = 0;
	ignore[0] = 1;
	ignore[1] = 1;
	index = 0;
	get_number_of_cmds(data);
	data->mini_cmds = malloc(sizeof(t_mini_data) * data->num_cmds);
	if (!data->mini_cmds)
		ft_error(NULL);
	while (data->cmd_line[++i])
	{
		if (data->cmd_line[i] == '\"' && ignore[1] == 1)
			ignore[0] *= -1;
		else if (data->cmd_line[i] == '\'' && ignore[0] == 1)
			ignore[1] *= -1;
		if (is_here(data->cmd_line[i], "|&") && ignore[1] + ignore[0] == 2)
			split_spliter(&data->mini_cmds[index++], &i, &j, data);
	}
	init_last_cmd(data, index, j, i);
	i = -1;
	while (++i < data->num_cmds)
		check_syntax_errors(&data->mini_cmds[i]);
}
