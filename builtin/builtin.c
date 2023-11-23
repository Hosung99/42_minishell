/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:46:45 by sgo               #+#    #+#             */
/*   Updated: 2023/11/23 16:56:36 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	ft_low_strncmp(char *s1, char *s2, size_t n);

void	builtin(t_cmd *cmd, t_info *info, t_envp *envp)
{
	g_exit_status = EXIT_SUCCESS;
	if (ft_low_strncmp(cmd->cmd[0], FT_ECHO, 5) == 0)
		ft_echo(cmd->cmd + 1);
	else if (ft_low_strncmp(cmd->cmd[0], CD, 3) == 0)
		ft_cd(cmd->cmd + 1, envp);
	else if (ft_low_strncmp(cmd->cmd[0], PWD, 4) == 0)
		ft_pwd();
	else if (ft_low_strncmp(cmd->cmd[0], EXPORT, 7) == 0)
		ft_export(cmd->cmd + 1, envp);
	else if (ft_low_strncmp(cmd->cmd[0], UNSET, 6) == 0)
		ft_unset(cmd->cmd + 1, envp);
	else if (ft_low_strncmp(cmd->cmd[0], ENV, 4) == 0)
		ft_env(envp);
	else if (ft_low_strncmp(cmd->cmd[0], EXIT, 5) == 0)
		ft_exit(cmd->cmd + 1, info);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	else if (ft_low_strncmp(cmd, FT_ECHO, 5) == 0)
		return (1);
	else if (ft_low_strncmp(cmd, CD, 3) == 0)
		return (1);
	else if (ft_low_strncmp(cmd, PWD, 4) == 0)
		return (1);
	else if (ft_low_strncmp(cmd, EXPORT, 7) == 0)
		return (1);
	else if (ft_low_strncmp(cmd, UNSET, 6) == 0)
		return (1);
	else if (ft_low_strncmp(cmd, ENV, 4) == 0)
		return (1);
	else if (ft_low_strncmp(cmd, EXIT, 5) == 0)
		return (1);
	else
		return (0);
}

static int	ft_low_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;
	char	c1;
	char	c2;

	i = 0;
	if (n == 0)
		return (0);
	if (!s1 || !s2)
		return (-1);
	while (i < n)
	{
		c1 = ft_tolower(s1[i]);
		c2 = ft_tolower(s2[i]);
		if (c1 != c2)
			return ((unsigned char)c1 - (unsigned char)c2);
		i++;
	}
	if (i == n)
		i--;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
