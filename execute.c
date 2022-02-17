/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 18:21:44 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/17 11:13:37 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executing(t_mini_data *mini_data, int **pipes, int index, int last_type)
{
	char	*cmd_path;
	char	**cmd_args;
	int		*fd_files;
	int		*her_pipe;

	her_pipe = NULL;
	cmd_path = NULL;
	g_data.save_out = dup(STDOUT_FILENO);
	g_data.save_tmp_fd = g_data.save_out;
	fd_files = open_files(mini_data);
	get_cmd_paths(mini_data, &cmd_path, &cmd_args);
	set_reder(mini_data, pipes, last_type, index);
	set_hd_and_f(mini_data, fd_files, her_pipe);
	close(g_data.save_out);
	if (execve(cmd_path, cmd_args, g_data.my_env) == -1)
		ft_error(NULL);
}

void	init_for_child(int *index, int *last_type, t_data *data, int **pipes)
{
	if (data->num_childs != 0)
		*last_type = data->mini_cmds[data->num_childs - 1].type;
	if (*last_type == PIPE && data->num_childs != 0)
	{
		(*index)++;
		close(pipes[*index - 1][WRITE]);
	}
}

void	s_exec_b_cmds(t_mini_data *m_data, int **pipes, int i, int l_type)
{
	int		*fd_files;
	int		*her_pipe;

	her_pipe = NULL;
	g_data.save_in = dup(STDIN_FILENO);
	g_data.save_out = dup(STDOUT_FILENO);
	g_data.save_tmp_fd = g_data.save_out;
	fd_files = open_files(m_data);
	set_reder(m_data, pipes, l_type, i);
	set_hd_and_f(m_data, fd_files, her_pipe);
	execute_builtins_cmds(m_data, l_type);
	dup2(g_data.save_in, STDIN_FILENO);
	dup2(g_data.save_out, STDOUT_FILENO);
	close(g_data.save_in);
	close(g_data.save_out);
}

int	creat_a_child(t_data *data, int **pipes, int i, int l_type)
{
	data->pid[data->num_childs] = fork();
	if (data->pid[data->num_childs] == -1)
		ft_error(NULL);
	else if (data->pid[data->num_childs] == 0)
		executing(&data->mini_cmds[data->num_childs], pipes, i, l_type);
	else
		if (wait_for_child(data, data->num_childs))
			return (1);
	return (0);
}

void	start_executing(t_data *data)
{
	int	**pipes;
	int	i;
	int	l_type;
	int	num_pipes;

	i = 0;
	init_to_start(data, &pipes, &num_pipes, &l_type);
	while (++data->num_childs < data->num_cmds)
	{
		init_for_child(&i, &l_type, data, pipes);
		if (!if_builtins_cmds(&data->mini_cmds[data->num_childs]))
		{
			data->pid[data->num_childs] = -1337;
			s_exec_b_cmds(&data->mini_cmds[data->num_childs], pipes, i, l_type);
			if (check_to_stop(data, data->num_childs))
				break ;
			continue ;
		}
		else if (creat_a_child(data, pipes, i, l_type))
			break ;
	}
	free(data->pid);
	free_all(data, pipes, num_pipes);
}
