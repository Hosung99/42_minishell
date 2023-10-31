/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 11:26:46 by sgo               #+#    #+#             */
/*   Updated: 2023/10/31 12:49:06 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	print_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[i])
	{
		printf("cmd[%d]: %s\n", i, cmd->cmd[i]);
		i++;
	}
	printf("cmd->str: %s\n", cmd->redir->str);
	printf("cmd->file_name: %s\n", cmd->redir->filename);
}

int	executor(t_cmd *cmd, t_envp *envp)
{
	t_info	info;
	
	init_info(&info, envp);
	while (cmd)
	{
		// print_cmd(cmd);
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
