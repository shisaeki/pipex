/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinsaeki <shinsaeki@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:21:34 by shinsaeki         #+#    #+#             */
/*   Updated: 2023/10/18 18:30:21 by shinsaeki        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(int infile, int outfile, char *cmd1, char *cmd2)
{
	char		**args1;
	char		**args2;
	int			fd[2];
	extern char	**environ;

	args1 = ft_split(cmd1, ' ');
	args2 = ft_split(cmd2, ' ');
	pipe(fd);
	if (fork() == 0)
	{
		dup2(infile, STDIN_FILENO);
		close(infile);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(get_command_fullpath(environ, args1), args1, environ);
	}
	wait(NULL);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	execve(get_command_fullpath(environ, args2), args2, environ);
}
