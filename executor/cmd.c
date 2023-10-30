/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 09:55:47 by sgo               #+#    #+#             */
/*   Updated: 2023/10/31 01:22:18 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*get_cmd(char **path, char *cmd)
{
	int		index;
	char	*path_cmd;
	char	*tmp;

	if (cmd == NULL || path == NULL)
		return (NULL);
	path_cmd = ft_strjoin("/", cmd);
	index = 0;
	while (path[index])
	{
		if (check_slash(cmd))
			tmp = ft_strdup(cmd);
		else
			tmp = ft_strjoin(path[index], path_cmd);
		if (access(tmp, X_OK) != -1)
		{
			free(path_cmd);
			return (tmp);
		}
		free(tmp);
		index++;
	}
	free(path_cmd);
	return (NULL);
}

int	check_slash(char *cmd)
{
	if (ft_strncmp(cmd, "/", 1) == 0
		|| ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd, "../", 3) == 0)
		return (1);
	return (0);
}
