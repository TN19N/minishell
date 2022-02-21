/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 20:12:37 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/21 11:01:35 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_env_ver(char **tok, int i, int j)
{
	char	*tmp;
	char	*env_ver;
	char	*env_value;

	env_ver = ft_substr(*tok, j, (i - j));
	if (!ft_strcmp(env_ver, "?"))
		env_value = ft_itoa(g_data.errsv);
	else if (!ft_strcmp(env_ver, "$"))
		env_value = ft_itoa(getpid());
	else
		env_value = ft_strdup(get_full_path(env_ver));
	free(env_ver);
	tmp = ft_substr(*tok, 0, j - 1);
	if (env_value)
	{
		env_ver = tmp;
		tmp = ft_strjoin(tmp, env_value);
		free(env_value);
		free(env_ver);
	}
	env_ver = ft_substr(*tok, i, ft_strlen(*tok) - i);
	free(*tok);
	*tok = ft_strjoin(tmp, env_ver);
	free(tmp);
	free(env_ver);
}

void	handl_env_ver(char **tok)
{
	int		j;
	int		i;

	i = -1;
	while ((*tok)[++i])
	{
		j = 0;
		if ((*tok)[i] == '$')
		{
			i++;
			j = i;
			while ((*tok)[i] && (ft_isalnum((*tok)[i]) || \
			is_here((*tok)[i], "?_")))
				i++;
			if (j != i || ((*tok)[i] == '$' && (*tok)[i - 1] == '$'))
			{
				if ((*tok)[i] == '$')
					i++;
				replace_env_ver(tok, i, j);
				i = -1;
			}
		}
	}
}

void	check_syntax_error(t_token **t)
{
	t_token	*token;

	token = (*t)->next;
	if (!token || token->type == REDIRECT_IN || token->type == REDIRECT_OUT || \
	token->type == REDIRECT_OUT_APP || token->type == HERE_DOC)
	{
		if (!token)
			ft_putendl_fd("minishell: syntax error \
near unexpected token `newline'", 2);
		else if (token->type == REDIRECT_IN)
			ft_putendl_fd("minishell: syntax error \
near unexpected token `<'", 2);
		else if (token->type == REDIRECT_OUT)
			ft_putendl_fd("minishell: syntax error \
near unexpected token `>'", 2);
		else if (token->type == REDIRECT_OUT_APP)
			ft_putendl_fd("minishell: syntax error \
near unexpected token `>>'", 2);
		else if (token->type == HERE_DOC)
			ft_putendl_fd("minishell: syntax error \
near unexpected token `<<'", 2);
		g_data.errsv = 258;
		free_all((*t)->data, NULL, 0);
		get_cmd_line();
	}
}

void	specefec_name(t_token **token, int *first_cmd)
{
	if ((*token)->last_type == NONE)
	{
		*first_cmd = 1;
		(*token)->type = CMD;
	}
	else if ((*token)->last_type == REDIRECT_IN)
		(*token)->type = IN_FILE;
	else if ((*token)->last_type == REDIRECT_OUT)
		(*token)->type = OUT_FILE;
	else if ((*token)->last_type == HERE_DOC)
		(*token)->type = DELIMTER;
	else if ((*token)->last_type == REDIRECT_OUT_APP)
		(*token)->type = OUT_FILE_APP;
	else
	{
		if (*first_cmd == 0)
		{
			(*token)->type = CMD;
			*first_cmd = 1;
		}
		else
			(*token)->type = ARGS;
	}
}

void	init_tokens(t_token **t, int *first_cmd)
{
	if ((*t)->type == WORD || (*t)->type == SINGLE_QUOTE || \
	(*t)->type == DOUBLE_QUOTE)
		specefec_name(t, first_cmd);
	else
		check_syntax_error(t);
}
