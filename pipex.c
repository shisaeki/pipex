/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinsaeki <shinsaeki@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:21:34 by shinsaeki         #+#    #+#             */
/*   Updated: 2023/10/18 18:24:46 by shinsaeki        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(int infile, int outfile, char *cmd1, char *cmd2, char **environ)
{
	char	**args1;
	char	**args2;
	char	*path_command1;
	char	*path_command2;
	int		fd[2];

	args1 = ft_split(cmd1, ' ');
	args2 = ft_split(cmd2, ' ');
	path_command1 = get_command_path(get_path_from_environ(environ), args1[0]);
	path_command2 = get_command_path(get_path_from_environ(environ), args2[0]);
	pipe(fd);
	if (fork() == 0)
	{
		dup2(infile, STDIN_FILENO);
		close(infile);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(path_command1, args1, environ);
	}
	wait(NULL);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	execve(path_command2, args2, environ);
}
