/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 11:26:46 by sgo               #+#    #+#             */
/*   Updated: 2023/11/17 16:49:19 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
void	print_redir(t_cmd *cmd);
void	print_cmd(t_cmd *cmd);
void	print_envp(t_envp *envp);

int	executor(t_cmd *cmd, t_envp *envp)
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
			break;
		}
		else
			info.pid = fork();
		if (info.pid == 0)
			child_process(cmd, &info, envp);
		else if (info.pid < 0)
			return (1);
		else
		{
			set_signal("ignore");
			parent_process(&info);
		}
		cmd = cmd->next;
		info.have_outfile = 0;
	}
	free_info(&info);
	if (cmd == NULL)
		wait_all(&info);
	set_signal("terminal");
	return (g_exit_status);
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

void	print_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	printf("start print	cmd\n");
	if (cmd == NULL)
		printf("cmd = NULL\n");
	else if (cmd->cmd && cmd->cmd[0] == NULL)
		printf("cmd->cmd = NULL\n");
	while (cmd->cmd && cmd->cmd[i])
	{
		printf("cmd[%d]: %s\n", i, cmd->cmd[i]);
		i++;
	}
	print_redir(cmd);
	printf("cmd 출력 완료\n");
}

void	print_envp(t_envp *envp)
{
	t_envp	*temp;

	temp = envp;
	printf("envp 출력 시작\n");
	while (temp)
	{
		printf("key: %s\n", temp->key);
		printf("value: %s\n", temp->value);
		temp = temp->next;
	}
	printf("envp 출력 완료\n");
}

void	print_redir(t_cmd *cmd)
{
	t_redir	*temp;

	if (cmd->redir == NULL)
	{
		printf("redir is NULL\n");
		return ;
	}
	temp = cmd->redir;
	while (temp)
	{
		printf("redir->str: %s\n", temp->str);
		printf("redir->filename: %s\n", temp->filename);
		temp = temp->next;
	}
}
