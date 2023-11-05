/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 11:26:46 by sgo               #+#    #+#             */
/*   Updated: 2023/11/05 19:33:28 by seoson           ###   ########.fr       */
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
	// print_envp(envp);
	init_info(&info, envp, cmd);
	while (cmd)
	{
		print_cmd(cmd);
		cmd = cmd->next;
	}
	// while (cmd)
	// {
	// 	print_cmd(cmd);
	// 	file_open(cmd, &info);
	// 	if (info.cmd_cnt == 1 && is_builtin(cmd->cmd[0]))
	// 	{	
	// 		builtin(cmd, &info, envp);
	// 		break;
	// 	}
	// 	else
	// 		info.pid = fork();
	// 	if (info.pid == 0)
	// 		child_process(cmd, &info);
	// 	else if (info.pid < 0)
	// 		return (1);
	// 	else
	// 		parent_process(&info);
	// 	cmd = cmd->next;
	// }
	// if (cmd == NULL)
	// 	wait_all(&info);
	return (info.status);
}

int	cmd_cnt(t_cmd *cmd)
{
	t_cmd	*temp;
	int		cnt;

	cnt = 0;
	temp  = cmd;
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
	if (cmd->cmd[0] == NULL)
		printf("cmd->cmd = NULL\n");
	while (cmd->cmd[i])
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
	// t_redir	*temp;

	// temp = cmd->redir;
	// while (temp)
	// {
	// 	printf("redir->str: %s\n", temp->str);
	// 	printf("redir->filename: %s\n", temp->filename);
	// 	temp = temp->next;
	// }
	if (cmd->redir == NULL)
	{
		printf("redir is NULL\n");
		return ;
	}
	while (cmd->redir)
	{
		printf("redir->str: %s\n", cmd->redir->str);
		printf("redir->filename: %s\n", cmd->redir->filename);
		cmd->redir = cmd->redir->next;
	}
}
