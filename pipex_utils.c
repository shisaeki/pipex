/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinsaeki <shinsaeki@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 21:50:03 by shinsaeki         #+#    #+#             */
/*   Updated: 2023/10/18 13:39:28 by shinsaeki        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path_from_environ(char **environ)
{
	char	**env;

	env = environ;
	while (*env)
	{
		if (ft_strncmp("PATH=", *env, 5) == 0)
			return (*env + 5);
		env++;
	}
	return (NULL);
}

char	*get_command_path(char *path, char *cmd)
{
	char	*path_copy;
	char	*result;
	char	*begin;
	char	*p;

	path_copy = ft_strdup(path);
	p = path_copy;
	while (p && *p)
	{
		begin = p;
		p = ft_strchr(begin, ':');
		if (p)
		{
			*p = '\0';
			p++;
		}
		result = ft_strjoin(ft_strjoin(begin, "/"), cmd);
		if (access(result, X_OK) == 0)
		{
			free(path_copy);
			return (result);
		}
		free(result);
	}
	free(path_copy);
	return (NULL);
}
