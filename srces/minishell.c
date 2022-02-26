/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:10:38 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/26 11:05:41 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	start(t_data *data)
{
	int	i;

	i = -1;
	if (get_mini_cmds(data))
		return ;
	while (++i < data->num_cmds)
	{
		if (get_tokens(data->mini_cmds[i].all_cmd, &data->mini_cmds[i]))
			return ;
	}
	start_executing(data);
}

static void	get_cmd_line(void)
{
	while (1337)
	{
		g_data.sig_int.sa_handler = &handler;
		if (sigaction(SIGINT, &g_data.sig_int, NULL) == -1)
			ft_error(NULL);
		g_data.cmd_line = readline("minishell:$ ");
		g_data.sig_int.sa_handler = &handler2;
		if (sigaction(SIGINT, &g_data.sig_int, NULL) == -1)
			ft_error(NULL);
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

static char	**copy_env(char **env)
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

static void	edit_attr(void)
{
	struct termios	settings;

	if (tcgetattr(STDIN_FILENO, &settings) == -1)
		ft_error(NULL);
	settings.c_lflag &= ~(ECHOCTL);
	if (tcsetattr(STDIN_FILENO, TCSANOW, &settings) == -1)
		ft_error(NULL);
}

int	main(int ac, char **av, char **env)
{
	struct sigaction	sig_quit;

	(void)ac;
	(void)av;
	g_data.first_pwd = 0;
	g_data.errsv = 0;
	edit_attr();
	g_data.my_env = copy_env(env);
	sig_quit.sa_handler = SIG_IGN;
	sig_quit.sa_flags = SA_RESTART;
	g_data.sig_int.sa_flags = SA_RESTART;
	if (sigaction(SIGQUIT, &sig_quit, NULL) == -1)
		ft_error(NULL);
	get_cmd_line();
	return (0);
}
