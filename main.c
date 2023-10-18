/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinsaeki <shinsaeki@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 21:53:00 by shinsaeki         #+#    #+#             */
/*   Updated: 2023/10/18 18:23:30 by shinsaeki        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **environ)
{
	int		fd_inflie;
	int		fd_outfile;
	char	*path;	

	path = get_path_from_environ(environ);
	fd_inflie = open(argv[1], O_RDONLY);
	fd_outfile = open(argv[4], O_WRONLY | O_CREAT, 0644);
	pipex(fd_inflie, fd_outfile, argv[2], argv[3], environ);
	return (0);
}
