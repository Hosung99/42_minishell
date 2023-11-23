/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 11:26:46 by sgo               #+#    #+#             */
/*   Updated: 2023/11/23 21:14:27 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	make_pipe(t_info *info, t_cmd *cmd, t_envp *envp);
int		execute(t_cmd *cmd, t_envp *envp, t_info *info);

void	executor(t_cmd *cmd, t_envp *envp)
{
	t_info	info;

	envp = envp->next;
	init_info(&info, envp, cmd);
	open_here_docs(&info, cmd);
	if (g_exit_status != EXIT_SUCCESS)
	{
		free_info(&info);
		return ;
	}
	if (execute(cmd, envp, &info) == 0)
		wait_all(cmd);
	free_info(&info);
	set_signal(TER, TER);
}

int	execute(t_cmd *cmd, t_envp *envp, t_info *info)
{
	if (info->cmd_cnt == 1 && is_builtin(cmd->cmd[0]))
	{
		if (file_open(cmd, info) == FAILURE)
			return (1);
		dup_stdout_builtin(info, cmd);
		builtin(cmd, info, envp);
		dup2(info->stdout_fd, STDOUT_FILENO);
		close(info->stdout_fd);
		return (1);
	}
	while (cmd)
	{
		file_open(cmd, info);
		if (pipe(info->pipe_fd) == -1)
			exit_perror("pipe", info);
		make_pipe(info, cmd, envp);
		cmd = cmd->next;
	}
	return (0);
}

void	make_pipe(t_info *info, t_cmd *cmd, t_envp *envp)
{
	set_signal(IGN, IGN);
	info->pid = fork();
	cmd->pid = info->pid;
	if (info->pid == 0)
	{
		set_signal(CHI, DEF);
		child_process(cmd, info, envp);
	}
	else if (info->pid < 0)
	{
		ft_perror("fork");
		exit_free(info);
	}
	else
		parent_process(info);
	info->have_outfile = 0;
}

int	cmd_cnt(t_cmd *cmd)
{
	t_cmd	*temp;
	int		cnt;

	cnt = 0;
	if (cmd == NULL)
		return (0);
	temp = cmd;
	while (temp)
	{
		cnt++;
		temp = temp->next;
	}
	return (cnt);
}
