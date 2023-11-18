/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 11:26:46 by sgo               #+#    #+#             */
/*   Updated: 2023/11/18 17:54:56 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	make_pipe(t_info *info, t_cmd *cmd, t_envp *envp);
void	print_redir(t_cmd *cmd);
void	print_cmd(t_cmd *cmd);
void	print_envp(t_envp *envp);

void	executor(t_cmd *cmd, t_envp *envp)
{
	t_info	info;

	envp = envp->next;
	init_info(&info, envp, cmd);
	open_here_docs(cmd);
	while (cmd)
	{
		if (pipe(info.pipe_fd) == -1)
			exit_perror("pipe", &info);
		file_open(cmd, &info);
		if (info.cmd_cnt == 1 && is_builtin(cmd->cmd[0]))
		{
			builtin(cmd, &info, envp);
			dup2(info.stdout_fd, STDOUT_FILENO);
			break ;
		}
		else
			make_pipe(&info, cmd, envp);
		cmd = cmd->next;
	}
	free_info(&info);
	if (cmd == NULL)
		wait_all(&info);
}

void	make_pipe(t_info *info, t_cmd *cmd, t_envp *envp)
{
	info->pid = fork();
	if (info->pid == 0)
		child_process(cmd, info, envp);
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
