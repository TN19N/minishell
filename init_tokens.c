/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 20:12:37 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/14 12:54:24 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_env_ver(char **tok, int i, int j)
{
	char	*tmp;
	char	*env_ver;
	char	*env_value;

	env_ver = ft_substr(*tok, j, (i - j));
	if (!ft_strcmp(env_ver, "?"))
		env_value = ft_itoa(data.errsv);
	else if (!ft_strcmp(env_ver, "$"))
		env_value = ft_itoa(getpid());
	else
		env_value = get_full_path(env_ver);
	free(env_ver);
	tmp = ft_substr(*tok, 0, j - 1);
	if (env_value)
	{
		env_ver = tmp;
		tmp = ft_strjoin(tmp, env_value);
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
			while ((*tok)[i] && (ft_isalnum((*tok)[i]) || (*tok)[i] == '?'))
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

void	check_syntax_error(t_token **token, int *last_type, int type)
{
	if (last_type[0] == REDIRECT_IN || last_type[0] == REDIRECT_OUT || \
	last_type[0] == REDIRECT_OUT_APP || last_type[0] == HERE_DOC)
	{
		if (type == REDIRECT_IN)
			ft_putendl_fd("minishell: syntax error \
near unexpected token `<'", 2);
		else if (type == REDIRECT_OUT)
			ft_putendl_fd("minishell: syntax error \
near unexpected token `>'", 2);
		else if (type == REDIRECT_OUT_APP)
			ft_putendl_fd("minishell: syntax error \
near unexpected token `>>'", 2);
		else if (type == HERE_DOC)
			ft_putendl_fd("minishell: syntax error \
near unexpected token `<<'", 2);
		data.errsv = 258;
		free_all((*token)->data, NULL, 0);
		get_cmd_line();
	}
	else
		(*token)->type = type;
}

void	specefec_name(t_token **token, int *last_type)
{
	if (last_type[0] == NONE)
	{
		last_type[1] = 1;
		(*token)->type = CMD;
	}
	else if (last_type[0] == REDIRECT_IN)
		(*token)->type = IN_FILE;
	else if (last_type[0] == REDIRECT_OUT)
		(*token)->type = OUT_FILE;
	else if (last_type[0] == HERE_DOC)
		(*token)->type = DELIMTER;
	else if (last_type[0] == REDIRECT_OUT_APP)
		(*token)->type = OUT_FILE_APP;
	else
	{
		if (last_type[1] == 0)
			(*token)->type = CMD;
		else
			(*token)->type = ARGS;
	}
}

void	init_tokens(t_token **token, int *last_type, int type)
{	
	if (type != SINGLE_QUOTE)
		handl_env_ver(&(*token)->tok);
	if (type == WORD || type == SINGLE_QUOTE || type == DOUBLE_QUOTE)
		specefec_name(token, last_type);
	else
		check_syntax_error(token, last_type, type);
}
