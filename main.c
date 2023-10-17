/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinsaeki <shinsaeki@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 21:53:00 by shinsaeki         #+#    #+#             */
/*   Updated: 2023/10/17 18:40:57 by shinsaeki        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main()
{
	int			fd_inflie;
	int			fd_outfile;
	int			fd[2];
    extern char	**environ;
	char		*path;	
	char		*cmd1;
	char		*cmd2;
	char		**args1;
	char		**args2;
	char		*path_command1;
	char		*path_command2;

    path = get_path_from_environ(environ);
	cmd1 = "ls -l";
	cmd2 = "wc -l";
	args1 = ft_split(cmd1, ' ');
	args2 = ft_split(cmd2, ' ');
	path_command1 = get_command_path(path, args1[0]);
	path_command2 = get_command_path(path, "wc");

	fd_inflie = open("./infile", O_RDONLY);
	fd_outfile = open("./outfile", O_WRONLY | O_CREAT, 0644);

	pipe(fd);
	if(fork() == 0)
	{
		dup2(fd_inflie, STDIN_FILENO);
		close(fd_inflie);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve(path_command1, args1, environ);
	}
	wait(NULL);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	dup2(fd_outfile, STDOUT_FILENO);
	close(fd_outfile);
	execve(path_command2, args2, environ);

    return (0);
}
