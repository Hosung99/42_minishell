/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 09:55:47 by sgo               #+#    #+#             */
/*   Updated: 2023/11/14 19:02:05 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*get_cmd(char **path, char *cmd, t_info *info)
{
	int		index;
	char	*path_cmd;
	char	*tmp;
	int		have_slash;

	have_slash = check_slash(cmd, info);

	if (cmd == NULL || path == NULL)
		return (NULL);
	path_cmd = ft_strjoin("/", cmd);
	index = 0;
	while (path[index])
	{
		if (have_slash == 1)
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
	if (have_slash == 1)
		exit_perror(cmd, info);
	return (NULL);
}

int	check_slash(char *cmd, t_info *info)
{
	struct stat	buf;
	int			index;

	stat(cmd, &buf);
	if ((buf.st_mode & S_IFMT) == S_IFDIR)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": is a directory\n", 2);
		g_exit_status = 126;
		exit_free(info);
	}
	index = 0;
	while (cmd[index])
	{
		if (cmd[index] == '/')
			return (1);
		index++;
	}
	return (0);
}
