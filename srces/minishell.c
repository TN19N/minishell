/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:10:38 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/21 06:58:22 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	start(t_data *data)
{
	int	i;

	i = -1;
	get_mini_cmds(data);
	while (++i < data->num_cmds)
		get_tokens(data->mini_cmds[i].all_cmd, &data->mini_cmds[i]);
	start_executing(data);
}

void	get_cmd_line(void)
{
	while (1337)
	{
		g_data.num_childs = -1;
		g_data.cmd_line = readline("minishell:$ ");
		if (!g_data.cmd_line)
		{
			printf("exit\n");
			exit(0);
		}
		if (ft_strlen(g_data.cmd_line) > 0)
		{
			add_history(g_data.cmd_line);
			if (if_just_spaces(g_data.cmd_line))
				free(g_data.cmd_line);
			else
				start(&g_data);
		}
		else
			free(g_data.cmd_line);
	}
}

char	**copy_env(char **env)
{
	int		tmp_count;
	char	**tmp_env;

	tmp_count = 0;
	while (env[tmp_count])
		tmp_count++;
	tmp_env = malloc(sizeof(char *) * (tmp_count + 1));
	if (!tmp_env)
		ft_error(NULL);
	tmp_count = 0;
	while (env[tmp_count])
	{
		tmp_env[tmp_count] = ft_strdup(env[tmp_count]);
		tmp_count++;
	}
	tmp_env[tmp_count] = NULL;
	g_data.count = tmp_count;
	return (tmp_env);
}

int	main(int ac, char **av, char **env)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	(void)ac;
	(void)av;
	g_data.first_pwd = 0;
	g_data.errsv = 0;
	g_data.my_env = copy_env(env);
	sig_int.sa_handler = &handler;
	sig_int.sa_flags = SA_NODEFER;
	sig_quit.sa_handler = SIG_IGN;
	sig_quit.sa_flags = SA_NODEFER;
	if (sigaction(SIGINT, &sig_int, NULL) == -1)
		ft_error(NULL);
	if (sigaction(SIGQUIT, &sig_quit, NULL) == -1)
		ft_error(NULL);
	get_cmd_line();
	return (0);
}
