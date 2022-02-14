/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnaciri- <hnaciri-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 10:17:07 by mannouao          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/02/14 16:25:12 by mannouao         ###   ########.fr       */
=======
/*   Updated: 2022/02/14 15:07:05 by hnaciri-         ###   ########.fr       */
>>>>>>> bebae7780885a6bc7f7933897317bbd13ff9f4de
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start(t_data *data)
{
	int i;
	// t_token *token;

	i = -1;
	get_mini_cmds(data);
	while (++i < data->num_cmds)
		get_tokens(data->mini_cmds[i].all_cmd, &data->mini_cmds[i]);
	//ft_env ();
	printf ("\n----------------------------------\n\n");
	ft_unset (data->mini_cmds);
	ft_env ();
	//system ("leaks minishell");
	//printf ("%s %d\n", data->mini_cmds->token_list->tok, data->mini_cmds->token_list->type);
	//printf ("%s %d\n", data->mini_cmds->token_list->next->tok, data->mini_cmds->token_list->next->type);
	//ft_pwd ();
	// i = -1;
	// printf("number of comds is : %d\n", data->num_cmds);
	// while (++i < data->num_cmds)
	// {
	// 	printf("(%s):\t", data->mini_cmds[i].all_cmd);
	// 	if (data->mini_cmds[i].type == PIPE)
	// 		printf("{PIPE}\n");
	// 	else if (data->mini_cmds[i].type == ANDLOG)
	// 		printf("{ANDLOG}\n");
	// 	else if (data->mini_cmds[i].type == ORLOG)
	// 		printf("{ORLOG}\n");
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
	//start_executing(data);
}

void	get_cmd_line(void)
{
	while (1337)
	{
		data.num_childs = -1;
		data.cmd_line = readline("minishell:$ ");
		if (!data.cmd_line)
<<<<<<< HEAD
			ft_exit();
=======
			ft_exit ();
>>>>>>> bebae7780885a6bc7f7933897317bbd13ff9f4de
		if (ft_strlen(data.cmd_line) > 0)
		{
			add_history(data.cmd_line);
			if (if_just_spaces(data.cmd_line))
				free(data.cmd_line);
			else
				start(&data);
		}
		else
			free(data.cmd_line);
	}
}

void	edit_attr(void)
{
	struct termios	old;

	tcgetattr(STDIN_FILENO, &old);
    //old.c_lflag &= ~ ECHO;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &old);
}

void	copy_env(char **env)
{
	data.count = 0;
	while (env[data.count])
		data.count++;
	data.my_env = malloc(sizeof(char *) * (data.count + 1));
	if (!data.my_env)
		ft_error(NULL);
<<<<<<< HEAD
	data.count = 0;
	while (env[data.count])
	{
		data.my_env[data.count] = ft_strdup(env[data.count]);
		data.count++;
	}
	data.my_env[data.count] = NULL;
=======
	count = -1;
	while (env[++count])
		data.my_env[count] = ft_strdup(env[count]);
	data.count = count;
	data.my_env[count] = NULL;
>>>>>>> bebae7780885a6bc7f7933897317bbd13ff9f4de
}

int	main(int ac, char **av, char **env)
{
	struct sigaction	sig_int;
	struct sigaction	sig_quit;

	(void)ac;
	(void)av;
	edit_attr ();
	data.errsv = 0;
	copy_env(env);
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
