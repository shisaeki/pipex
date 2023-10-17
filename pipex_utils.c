/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shinsaeki <shinsaeki@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 21:50:03 by shinsaeki         #+#    #+#             */
/*   Updated: 2023/10/17 18:38:03 by shinsaeki        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char    *get_path_from_environ(char **environ)
{
    char    **env;

    env = environ;
    while (*env)
    {
        if (ft_strncmp("PATH=", *env, 5) == 0)
        {
            return (*env + 5);
        }
        env++;
    }
    return (NULL);
}

char	*get_command_path(char *path, char *cmd)
{
	char	*path_copy;
	char	*result;
	char	*tmp;
	char	*begin;
	char	*p;
	
	path_copy = ft_strdup(path);
	result = NULL;
	p = path_copy;
	while (p != NULL && *p != '\0')
	{
		begin = p;
		p = ft_strchr(p, ':');
		if (p != NULL)
		{
			*p = '\0';
			p++;
		}
		tmp = ft_strjoin(begin, "/");
		result = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(result, X_OK) == 0)
			return (result);
		if (result != NULL)
			free(result);
	}
	return (NULL);
}
