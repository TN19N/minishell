/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmds3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:40:38 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/15 20:04:50 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	grep_pwd(char *s)
{
	int	i;

	i = -1;
	while (g_data.my_env[++i])
		if (!ft_strncmp(g_data.my_env[i], s, ft_strlen(s)))
			return (i);
	return (-1);
}

void	ft_setpwd(char *old)
{
	static int	just_ones;
	int			i;
	char		*new;
	char		**temp;

	new = getcwd (NULL, 0);
	i = grep_pwd("PWD=");
	if (i != -1)
	{
		free (g_data.my_env[i]);
		g_data.my_env[i] = ft_strjoin ("PWD=", new);
	}
	free (new); 
	i = grep_pwd("OLDPWD=");
	if (just_ones == 0 && i == -1)
	{
		temp = malloc(sizeof(char *) * (g_data.count + 2));
		if (!temp)
			ft_error(NULL);
		temp = copy_env(g_data.my_env);
		temp[g_data.count++] = ft_strjoin ("OLDPWD=", old);
		temp[g_data.count] = NULL;
		ft_free(g_data.my_env);
		g_data.my_env = temp;;
		just_ones = 1;
	}
	else if (i != -1)
	{
		free (g_data.my_env[i]);
		g_data.my_env[i] = ft_strjoin("OLDPWD=", old);
	}
	free (old);
}

void	cd_error(char *str)
{
	g_data.errsv = 1;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": No such file or directory", 2);
}

void	ft_cd(t_mini_data *mini_data)
{
	t_token	*head;
	char	*old;

	old = getcwd(NULL, 0);
	head = mini_data->token_list;
	g_data.errsv = 0;
	if (head->next && head->next->type == ARGS)
	{
		if (chdir(head->next->tok))
		{
			free(old);
			cd_error(head->next->tok);
		}
		else
			ft_setpwd(old);
		return ;
	}
	if (chdir(get_full_path("HOME")))
	{
		free(old);
		no_home_for_cd();
	}
	else
		ft_setpwd(old);
}
