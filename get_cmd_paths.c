/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_paths.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 10:39:54 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/19 10:54:00 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_cmd_path(char *cmd, char **mini_paths)
{
	int		i;
	char	*tmp;
	char	*cmd_path;

	i = -1;
	tmp = ft_strjoin("/", cmd);
	while (mini_paths[++i])
	{
		cmd_path = ft_strjoin(mini_paths[i], tmp);
		if (!access(cmd_path, F_OK))
		{
			ft_free(mini_paths);
			free(tmp);
			return (cmd_path);
		}
		free(cmd_path);
	}
	ft_free(mini_paths);
	free(tmp);
	return (NULL);
}

void	command_error_no_path(char *cmd)
{
	printf("minishell: ");
	printf("%s", cmd);
	printf(": No such file or directory\n");
	exit(127);
}

char	*check_cmd_path(char *cmd)
{
	int		i;
	char	*full_path;
	char	*cmd_path;

	i = 0;
	if (!access(cmd, F_OK))
	{
		if (!access(cmd, X_OK))
			return (cmd);
		else
		{
			g_data.errsv = 126;
			ft_error(cmd);
		}
	}
	full_path = get_full_path("PATH");
	if (!full_path)
		command_error_no_path(cmd);
	cmd_path = get_cmd_path(cmd, ft_split(full_path, ':'));
	if (cmd_path)
		return (cmd_path);
	g_data.errsv = 127;
	return (NULL);
}

void	get_cmd_paths(t_mini_data *mini_data, char **cmd_path, char ***c_args)
{
	int		count;
	t_token	*token;

	count = 1;
	count += number_of_types(mini_data, ARGS);
	*c_args = malloc(sizeof(char *) * (count + 1));
	if (!*c_args)
		ft_error(NULL);
	token = mini_data->token_list;
	count = 0;
	while (token)
	{
		if (token->type == CMD)
		{
			(*c_args)[count++] = ft_strdup(token->tok);
			*cmd_path = check_cmd_path(token->tok);
			if (!*cmd_path)
				ft_error(token->tok);
		}
		else if (token->type == ARGS)
			(*c_args)[count++] = ft_strdup(token->tok);
		token = token->next;
	}
	(*c_args)[count] = NULL;
}
