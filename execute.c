/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 18:21:44 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/15 17:06:26 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*open_files(t_mini_data *mini_data)
{
	int		num_fd;
	int		*fd;
	t_token	*token;

	num_fd = number_of_types(mini_data, OUT_FILE);
	num_fd += number_of_types(mini_data, IN_FILE);
	num_fd += number_of_types(mini_data, OUT_FILE_APP);
	if (num_fd == 0)
		return (NULL);
	fd = malloc(sizeof(int) * (num_fd + 1));
	if (!fd)
		ft_error(NULL);
	fd[num_fd--] = -1;
	token = mini_data->token_list;
	while (token)
	{
		creat_files(token, fd, &num_fd);
		token = token->next;
	}
	return (fd);
}

void	executing(t_mini_data *mini_data, int **pipes, int index, int last_type)
{
	char	*cmd_path;
	char	**cmd_args;
	int		*fd_files;
	int		*her_pipe;

	her_pipe = NULL;
	cmd_path = NULL;
	fd_files = open_files(mini_data);
	get_cmd_paths(mini_data, &cmd_path, &cmd_args);
	set_her_doc_and_files(mini_data, fd_files, her_pipe);
	set_rederactions(mini_data, pipes, last_type, index);
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

void	start_executing_b_cmds(t_mini_data *mini_data, int **pipes, int index, int last_type)
{
	int		*fd_files;
	int		*her_pipe;
	int		save_out;
	int		save_in;

	her_pipe = NULL;
	save_in = dup(STDIN_FILENO);
	save_out = dup(STDOUT_FILENO);
	fd_files = open_files(mini_data);
	set_her_doc_and_files(mini_data, fd_files, her_pipe);
	set_rederactions(mini_data, pipes, last_type, index);
	execute_builtins_cmds(mini_data, last_type);
	dup2(save_in, STDIN_FILENO);
	dup2(save_out, STDOUT_FILENO);
	close(save_in);
	close(save_out);
}

void	start_executing(t_data *data)
{
	int	**pipes;
	int	index;
	int	l_type;
	int	num_pipes;

	index = 0;
	num_pipes = get_pipes(data, &pipes);
	l_type = LASTONE;
	data->pid = malloc(sizeof(int) * data->num_cmds);
	if (!data->pid)
		ft_error(NULL);
	while (++data->num_childs < data->num_cmds)
	{
		init_for_child(&index, &l_type, data, pipes);
		if (!if_builtins_cmds(&data->mini_cmds[data->num_childs]))
		{
			data->pid[data->num_childs] = -1337;
			start_executing_b_cmds(&data->mini_cmds[data->num_childs], pipes, index, l_type);
			if (data->mini_cmds[data->num_childs].type == ORLOG && g_data.errsv == 0)
				break ;
			else if (data->mini_cmds[data->num_childs].type == ANDLOG && g_data.errsv != 0)
				break ;
			continue ;
		}
		data->pid[data->num_childs] = fork();
		if (data->pid[data->num_childs] == -1)
			ft_error(NULL);
		else if (data->pid[data->num_childs] == 0)
			executing(&data->mini_cmds[data->num_childs], pipes, index, l_type);
		else
			if (wait_for_child(data, data->num_childs))
				break ;
	}
	free(data->pid);
	free_all(data, pipes, num_pipes);
}
