/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 11:26:39 by hnaciri-          #+#    #+#             */
/*   Updated: 2022/02/26 08:54:08 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_export(t_token *token)
{
	int	i;

	i = -1;
	if (token->type != ARGS)
		return (0);
	if ((!ft_isalpha(token->tok[0]) || token->tok[0] == '=') \
	&& token->tok[0] != '_')
		return (-1);
	while (token->tok[++i])
	{		
		if (!ft_isalnum(token->tok[i]) \
			&& token->tok[i] != '_' && token->tok[i] != '=')
			return (-1);
		if (token->tok[i] == '=')
			break ;
	}
	if (token->tok[i] && is_here(token->tok[i], " \t\n\v\f\r"))
		return (-1);
	if (token->tok[i] == '=')
		return (1);
	return (0);
}

int	ft_grep(char *s)
{
	int		i;
	char	*temp;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	temp = ft_calloc(sizeof(char), i + 1);
	if (!temp)
		ft_error(NULL);
	i = -1;
	while (s[++i] && s[i] != '=')
		temp[i] = s[i];
	temp[i] = '\0';
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

	new_env = ft_calloc(sizeof(char *), g_data.count + 1);
	if (!new_env)
		ft_error(NULL);
	i = -1;
	while (g_data.my_env[++i])
		new_env[i] = ft_strdup(g_data.my_env[i]);
	token = grep_a_type(mini_data->token_list, CMD)->next;
	while (token)
	{
		if (token->type == ARGS)
		{
			if (ft_check_export(token) && ft_check_export(token) != -1 \
			&& ft_grep(token->tok) == -1)
				new_env[i++] = ft_strdup(token->tok);
		}
		token = token->next;
	}
	new_env[i] = 0;
	ft_free (g_data.my_env);
	g_data.my_env = new_env;
}

void	export_old(t_token *token, t_mini_data *mini_data)
{
	int	i;

	token = grep_a_type(mini_data->token_list, CMD)->next;
	while (token)
	{	
		if (token->type == ARGS)
		{
			i = ft_grep(token->tok);
			if (i != -1 && ft_check_export(token) != -1)
			{
				free (g_data.my_env[i]);
				g_data.my_env[i] = ft_strdup(token->tok);
			}
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
	token = grep_a_type(mini_data->token_list, CMD);
	token = token->next;
	while (token)
	{	
		if (token->type == ARGS)
		{
			i = ft_check_export(token);
			if (i == -1)
			{
				g_data.errsv = 1;
				ft_unset_export_err(token->tok, 0);
			}
			else if (i && ft_grep(token->tok) == -1)
				g_data.count++;
		}
		token = token->next;
	}
	export_old(token, mini_data);
	export_new(new_env, token, mini_data);
}
