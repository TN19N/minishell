/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 18:21:44 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/14 18:11:19 by mannouao         ###   ########.fr       */
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

void	dup_all_files(t_mini_data *mini_data, int *fd)
{
	int		i;
	t_token	*token;

	i = 0;
	while (fd[i] != -1)
		i++;
	i--;
	token = mini_data->token_list;
	while (token)
	{
		if (token->type == OUT_FILE)
			dup2(fd[i--], STDOUT_FILENO);
		else if (token->type == IN_FILE)
			dup2(fd[i--], STDIN_FILENO);
		else if (token->type == OUT_FILE_APP)
			dup2(fd[i--], STDOUT_FILENO);
		token = token->next;
	}
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
	if (if_builtins_cmds(mini_data))
		get_cmd_paths(mini_data, &cmd_path, &cmd_args);
	here_doc(mini_data, her_pipe);
	if (fd_files)
		dup_all_files(mini_data, fd_files);
	if (mini_data->type == PIPE)
		dup2(pipes[index][WRITE], STDOUT_FILENO);
	if (last_type == PIPE)
		dup2(pipes[index - 1][READ], STDIN_FILENO);
	if (!if_builtins_cmds(mini_data))
		execute_builtins_cmds(mini_data);
	else
	{
		if (execve(cmd_path, cmd_args, data.my_env) == -1)
			ft_error(NULL);
	}
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

void	start_executing(t_data *data)
{
	int	**pipes;
	int	index;
	int	last_type;
	int	num_pipes;

	index = 0;
	num_pipes = get_pipes(data, &pipes);
	last_type = LASTONE;
	data->pid = malloc(sizeof(int) * data->num_cmds);
	if (!data->pid)
		ft_error(NULL);
	while (++data->num_childs < data->num_cmds)
	{
		init_for_child(&index, &last_type, data, pipes);
		data->pid[data->num_childs] = fork();
		if (data->pid[data->num_childs] == -1)
			ft_error(NULL);
		else if (data->pid[data->num_childs] == 0)
			executing(&data->mini_cmds[data->num_childs], pipes, index, last_type);
		else
			if (wait_for_child(data, data->num_childs))
				break ;
	}
	free(data->pid);
	free_all(data, pipes, num_pipes);
}
