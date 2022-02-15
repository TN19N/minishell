/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 18:10:27 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/15 09:33:55 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# define READ 0
# define WRITE 1

# define PIPE 1
# define ANDLOG 2
# define ORLOG 3
# define LASTONE 4

# define NONE 1
# define DOUBLE_QUOTE 2
# define SINGLE_QUOTE 3
# define HERE_DOC 4
# define REDIRECT_IN 5
# define REDIRECT_OUT 6
# define REDIRECT_OUT_APP 7
# define CMD 8
# define ARGS 9 
# define DELIMTER 10
# define OUT_FILE 11
# define OUT_FILE_APP 12
# define IN_FILE 13
# define WORD 14

# include <fcntl.h>
# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>

typedef struct s_data	t_data;

t_data					g_data;

typedef struct s_token
{
	char			*tok;
	int				type;
	struct s_token	*next;
	t_data			*data;
}					t_token;

typedef struct s_mini_data
{
	int		type;
	char	*all_cmd;
	t_token	*token_list;
	t_data	*data;
}			t_mini_data;

typedef struct s_data
{
	int			count;
	int			num_childs;
	int			errsv;
	int			*pid;
	char		**my_env;
	char		*cmd_line;
	int			num_cmds;
	t_mini_data	*mini_cmds;
}				t_data;

void	ft_error(char *str);
void	execute(char **cmd_line, int **fd, int i, int num_cmd);
void	handler(int sig);
void	free_2d_table(char **table);
void	get_cmd_line(void);
int		**init_pipe(int num_cmds);
void	parsing(t_data *data);
int		is_here(char c, char *str);
void	mini_init(int *i, int *count, int *ignore);
int		sum_arr(int *ignore);
void	get_mini_cmds(t_data *data);
void	get_tokens(char *cmd_line, t_mini_data *mini_cmd);
t_token	*token_init(t_data *data);
void	check_if_token_full(t_token **token, int *last_type);
int		if_just_spaces(char *str);
void	check_syntax_errors(t_mini_data *mini_data);
void	init_tokens(t_token **token, int *last_type, int type);
char	*get_full_path(char *to_find);
void	start_executing(t_data *data);
int		number_of_types(t_mini_data *mini_data, int type);
void	start_executing(t_data *data);
void	get_cmd_paths(t_mini_data *mini_data, char **cmd_path, char ***c_args);
int		here_doc(t_mini_data *mini_data, int *her_pipe);
int		get_pipes(t_data *data, int ***pipes);
void	creat_files(t_token *token, int *fd, int *num_fd);
int		wait_for_child(t_data *data, int i);
void	free_all(t_data *data, int **pipes, int count);
void	set_signals(void);
int		if_builtins_cmds(t_mini_data *mini_data);
void	ft_exit(void);
void	ft_env(void);
int		ft_check(t_token *head, char *env);
int		ft_is_valid(char *s);
int		ft_is_in(char *s);
void	execute_builtins_cmds(t_mini_data *mini_data);
void	ft_unset(t_mini_data *mini_data);
void	ft_pwd(void);
void	ft_unset_err(char *s);
t_token	*grep_a_type(t_token *token, int type);
char	**alloc_new_env(t_token *head, int *tmp, int *check_if_err);
void	ft_env(void);
void	ft_exit(void);
void	ft_pwd(void);
void	ft_unset(t_mini_data *l);
void	edit_attr(void);
void	ft_unset_err(char *s);
void	check_syntax(t_data *data);
void	set_her_doc_and_files(t_mini_data *mini_data, int *fd_files, int *her_pipe);
void	set_rederactions(t_mini_data *mini_data, int **pipes, int last_type, int index);
void	dup_all_files(t_mini_data *mini_data, int *fd);

#endif