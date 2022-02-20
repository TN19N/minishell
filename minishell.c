/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:10:38 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/20 09:12:45 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start(t_data *data)
{
	int i;
	//t_token *token;

	i = -1;
	get_mini_cmds(data);
	while (++i < data->num_cmds)
		get_tokens(data->mini_cmds[i].all_cmd, &data->mini_cmds[i]);
	// i = -1;
	// printf("number of comds is : %d\n", data->num_cmds);
	// while (++i < data->num_cmds)
	// {
	// 	printf("(%s):\t", data->mini_cmds[i].all_cmd);
	// 	if (data->mini_cmds[i].type == PIPE)
	// 		printf("{PIPE}\n");
	// 	else if (data->mini_cmds[i].type == LASTONE)
	// 		printf("{LASTONE}\n");
	// 	token = data->mini_cmds[i].token_list;
	// 	while (token)
	// 	{
	// 		printf("\t[%s]\t", token->tok);
	// 		if (token->type == CMD)
	// 			printf("(CMD)\n");
	// 		else if (token->type == ARGS)
	// 			printf("(ARGS)\n");
	// 		else if (token->type == OUT_FILE_APP)
	// 			printf("(OUT_FILE_APP)\n");
	// 		else if (token->type == OUT_FILE)
	// 			printf("(OUT_FILE)\n");
	// 		else if (token->type == IN_FILE)
	// 			printf("(IN_FILE)\n");
	// 		else if (token->type == HERE_DOC)
	// 			printf("(HERE_DOC)\n");
	// 		else if (token->type == DELIMTER)
	// 			printf("(DELIMITER)\n");
	// 		else if (token->type == REDIRECT_OUT_APP)
	// 			printf("(REDIRECT_OUT_APP)\n");
	// 		else if (token->type == REDIRECT_OUT)
	// 			printf("REDIRECT_OUT\n");
	// 		else if (token->type == REDIRECT_IN)
	// 			printf("REDIRECT_IN\n");
	// 		token = token->next;
	// 	}
	// }
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
