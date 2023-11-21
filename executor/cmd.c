/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 09:55:47 by sgo               #+#    #+#             */
/*   Updated: 2023/11/21 18:33:35 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*attach_cmd(char *path, char *cmd, int have_slash, char *path_cmd);

char	*get_cmd(char **path, char *cmd, t_info *info)
{
	int		index;
	char	*path_cmd;
	char	*tmp;
	int		have_slash;

	if (cmd == NULL || path == NULL)
		return (NULL);
	if (cmd[0] == '\0')
		ft_cmd_error(cmd);
	have_slash = check_slash(cmd, info);
	path_cmd = ft_strjoin("/", cmd);
	index = 0;
	while (path[index])
	{
		tmp = attach_cmd(path[index], cmd, have_slash, path_cmd);
		if (tmp != NULL)
			return (tmp);
		index++;
	}
	ft_free(path_cmd);
	if (have_slash == 1)
		exit_perror(cmd, info);
	return (NULL);
}

char	*attach_cmd(char *path, char *cmd, int have_slash, char *path_cmd)
{
	char	*tmp;

	if (have_slash == 1)
		tmp = ft_strdup(cmd);
	else
	tmp = ft_strjoin(path, path_cmd);
	if (access(tmp, X_OK) != -1)
		return (tmp);
	ft_free(tmp);
	return (NULL);
}

int	check_slash(char *cmd, t_info *info)
{
	struct stat	buf;
	int			index;

	stat(cmd, &buf);
	if ((buf.st_mode & S_IFMT) == S_IFDIR)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": is a directory\n", STDERR_FILENO);
		g_exit_status = EXIT_NOT_DIR;
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
