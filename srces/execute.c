/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 18:21:44 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/25 14:20:54 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec(t_mini_data *mini_data, int **pipes, int index, int last_type)
{
	char	*cmd_path;
	char	**cmd_args;
	int		*fd_files;

	cmd_path = NULL;
	fd_files = open_files(mini_data);
	set_reder(mini_data, pipes, last_type, index);
	set_hd_and_f(mini_data, fd_files);
	if (!grep_a_type(mini_data->token_list, CMD))
		exit(EXIT_SUCCESS);
	get_cmd_paths(mini_data, &cmd_path, &cmd_args);
	if (fd_files)
		free(fd_files);
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
		pipes[*index - 1][WRITE] = -1337;
	}
}

void	b_cmds(t_mini_data *mini_data, int **pipes, int index, int l_type)
{
	int	*fd_files;

	g_data.save_out = dup(STDOUT_FILENO);
	g_data.save_in = dup(STDIN_FILENO);
	fd_files = open_files(mini_data);
	set_reder(mini_data, pipes, l_type, index);
	set_hd_and_f(mini_data, fd_files);
	execute_builtins_cmds(mini_data);
	if (fd_files)
		free(fd_files);
	dup2(g_data.save_in, STDIN_FILENO);
	dup2(g_data.save_out, STDOUT_FILENO);
	close(g_data.save_in);
	close(g_data.save_out);
}

void	creat_childernes(t_data *data, int *i, int *l_type, int **pipes)
{
	while (data->num_childs < data->num_cmds)
	{
		init_for_child(i, l_type, data, pipes);
		data->pid[data->num_childs] = fork();
		if (data->pid[data->num_childs] == -1)
			ft_error(NULL);
		else if (data->pid[data->num_childs] == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (!if_builtins_cmds(&data->mini_cmds[data->num_childs]))
			{
				b_cmds(&data->mini_cmds[data->num_childs], pipes, *i, *l_type);
				exit(g_data.errsv);
			}
			else
				exec(&data->mini_cmds[data->num_childs], pipes, *i, *l_type);
		}
		close_last_pipe(data, pipes, i);
		data->num_childs++;
	}
	wait_for_child(data);
}

void	start_executing(t_data *data)
{
	int	**pipes;
	int	i;
	int	l_type;
	int	num_pipes;

	i = 0;
	data->num_childs = 0;
	if (creat_child_for_heredoc(data))
	{
		free_all(data, NULL, 0);
		return ;
	}
	init_to_start(data, &pipes, &num_pipes, &l_type);
	if (!if_builtins_cmds(&data->mini_cmds[data->num_childs]) && \
	data->mini_cmds[data->num_childs].type != PIPE)
		b_cmds(&data->mini_cmds[data->num_childs], pipes, i, l_type);
	else
		creat_childernes(data, &i, &l_type, pipes);
	free(data->pid);
	free_all(data, pipes, num_pipes);
}
