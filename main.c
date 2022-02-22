/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mannouao <mannouao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:09:08 by mannouao          #+#    #+#             */
/*   Updated: 2022/02/22 20:13:53 by mannouao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "includes/minishell.h"

int main()
{
	int fd_1;
	int	fd[2];

	pipe(fd);

	if (fork() == 0)
	{	
		fd_1 = open("test.txt", O_RDONLY | O_CREAT, 0644);
		printf(" %d %d %d \n", fd_1, fd[0], fd[1]);
	}
	else
		wait(NULL);
	fd_1 = open("test.txt", O_RDONLY | O_CREAT, 0644);
	printf(" %d %d %d \n", fd_1, fd[0], fd[1]);
}