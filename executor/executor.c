/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 11:26:46 by sgo               #+#    #+#             */
/*   Updated: 2023/11/01 20:00:14 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
void	print_redir(t_cmd *cmd);
void	print_cmd(t_cmd *cmd);
void	print_envp(t_envp *envp);

int	executor(t_cmd *cmd, t_envp *envp)
{
	t_info	info;
	
	printf("start executor\n");
	print_cmd(cmd);
	print_envp(envp);
	init_info(&info, envp);
	while (cmd)
	{
		print_cmd(cmd);
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

void	print_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[i])
	{
		printf("cmd[%d]: %s\n", i, cmd->cmd[i]);
		i++;
	}
	printf("cmd 출력 완료\n");
	print_redir(cmd);
	printf("cmd->file_name: %s\n", cmd->redir->filename);
}

void	print_envp(t_envp *envp)
{
	t_envp	*temp;

	temp = envp;
	while (temp)
	{
		printf("key: %s\n", temp->key);
		printf("value: %s\n", temp->value);
		temp = temp->next;
	}
}

void	print_redir(t_cmd *cmd)
{
	t_redir	*temp;

	temp = cmd->redir;
	while (temp)
	{
		printf("redir->str: %s\n", temp->str);
		printf("redir->filename: %s\n", temp->filename);
		temp = temp->next;
	}
}
