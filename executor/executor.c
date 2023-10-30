/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 11:26:46 by sgo               #+#    #+#             */
/*   Updated: 2023/10/31 01:31:29 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	executor(t_cmd *cmd, t_envp *envp)
{
	t_info	info;
	
	init_info(&info, envp);
	while (cmd)
	{
		file_open(cmd, &info);
		if (is_builtin(cmd->cmd[0]))
			builtin(cmd, &info, envp);
		else
			info.pid = fork();
		if (info.pid == 0)
			child_process(cmd, &info);
		else if (info.pid < 0)
			return (1);
		else
			parent_process(&info);
		cmd = cmd->next;
		info.cnt++;
	}
	wait_all(&info);
	return (info.status);
}
