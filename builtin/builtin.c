/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:46:45 by sgo               #+#    #+#             */
/*   Updated: 2023/11/21 19:10:51 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	builtin(t_cmd *cmd, t_info *info, t_envp *envp)
{
	g_exit_status = EXIT_SUCCESS;
	dup_stdout(info, cmd);
	if (ft_strncmp(cmd->cmd[0], FT_ECHO, 5) == 0)
		ft_echo(cmd->cmd + 1);
	else if (ft_strncmp(cmd->cmd[0], CD, 3) == 0)
		ft_cd(cmd->cmd + 1, envp);
	else if (ft_strncmp(cmd->cmd[0], PWD, 4) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd->cmd[0], EXPORT, 7) == 0)
		ft_export(cmd->cmd + 1, envp);
	else if (ft_strncmp(cmd->cmd[0], UNSET, 6) == 0)
		ft_unset(cmd->cmd + 1, envp);
	else if (ft_strncmp(cmd->cmd[0], ENV, 4) == 0)
		ft_env(envp);
	else if (ft_strncmp(cmd->cmd[0], EXIT, 5) == 0)
		ft_exit(cmd->cmd + 1, info);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	else if (ft_strncmp(cmd, FT_ECHO, 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, CD, 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, PWD, 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, EXPORT, 7) == 0)
		return (1);
	else if (ft_strncmp(cmd, UNSET, 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, ENV, 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, EXIT, 5) == 0)
		return (1);
	else
		return (0);
}
