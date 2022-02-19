/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 11:26:39 by hnaciri-          #+#    #+#             */
/*   Updated: 2022/02/19 07:56:30 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_export(t_token *token)
{
	int	i;

	i = -1;
	if (token->type != ARGS)
		return (0);
	if (!ft_isalpha(token->tok[0]))
		return (-1);
	while (token->tok[++i])
	{
		if (!ft_isalnum (token->tok[i]) && token->tok[i] != '=')
			return (-1);
		if (token->tok[i] == '=')
			break ;
	}
	if (token->tok[i] == '=')
		return (1);
	return (0);
}

int	ft_grep(char *s)
{
	int		i;
	char	*temp;

	i = 0;
	while (s[i] != '=')
		i++;
	temp = ft_calloc(sizeof(char), i + 1);
	if (!temp)
		ft_error(NULL);
	i = -1;
	while (s[++i] != '=')
		temp[i] = s[i];
	temp[i] = 0;
	i = -1;
	while (g_data.my_env[++i])
	{
		if (!ft_strncmp(g_data.my_env[i], temp, ft_strlen(temp)))
		{
			free (temp);
			return (i);
		}
	}
	free (temp);
	return (-1);
}

void	export_new(char **new_env, t_token *token, t_mini_data *mini_data)
{
	int	i;

	i = -1;
	while (g_data.my_env[++i])
		new_env[i] = ft_strdup (g_data.my_env[i]);
	token = mini_data->token_list->next;
	while (token)
	{
		if (ft_check_export (token) && ft_check_export (token) != -1 \
		&& ft_grep(token->tok) == -1)
			new_env[i++] = ft_strdup (token->tok);
		token = token->next;
	}
	new_env[i] = 0;
	ft_free (g_data.my_env);
	g_data.my_env = new_env;
}

void	export_old(char **new_env, t_token *token, t_mini_data *mini_data)
{
	int	i;

	token = mini_data->token_list->next;
	new_env = ft_calloc (sizeof(char *), g_data.count + 1);
	if (!new_env)
		ft_error(NULL);
	while (token)
	{
		i = ft_grep (token->tok);
		if (i != -1)
		{
			free (g_data.my_env[i]);
			g_data.my_env[i] = ft_strdup (token->tok);
		}
		token = token->next;
	}
}

void	ft_export(t_mini_data *mini_data)
{
	t_token	*token;
	char	**new_env;
	int		i;

	new_env = NULL;
	if (!mini_data->token_list->next)
		return ;
	token = mini_data->token_list->next;
	while (token)
	{
		i = ft_check_export(token);
		if (i == -1)
			ft_unset_export_err(token->tok, 0);
		else if (i && ft_grep(token->tok) == -1)
			g_data.count++;
		if (i == -1)
			g_data.errsv = 1;
		token = token->next;
	}
	export_old(new_env, token, mini_data);
	export_new(new_env, token, mini_data);
}
