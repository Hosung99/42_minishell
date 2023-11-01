/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:46:45 by sgo               #+#    #+#             */
/*   Updated: 2023/10/31 00:58:10 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	builtin(t_cmd *cmd, t_info *info, t_envp *envp)
{
	//아직 buitin 함수들 형태만 구현함
	
	if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
		echo(cmd->cmd + 1);
	else if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
		ft_cd(cmd->cmd + 1, info, envp);
	else if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(cmd->cmd[0], "export", 7) == 0)
		ft_export(cmd->cmd + 1, info, envp);
	else if (ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
		ft_unset(cmd->cmd + 1, info, envp);
	else if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
		ft_env(envp);
	else if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
		ft_exit(cmd, info, envp);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	else if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	else
		return (0);
}