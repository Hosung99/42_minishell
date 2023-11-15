/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:18:12 by sgo               #+#    #+#             */
/*   Updated: 2023/11/15 17:04:59 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	child_process(t_cmd *cmd, t_info *info)
{
	close(info->pipe_fd[0]);
	dup_stdout(info, cmd);
	if (info->tmp_fd < 0)
		exit(0); // exit 전에 free 해줘야함
	if (dup2(info->tmp_fd, STDIN_FILENO) == -1)
		exit_perror("DUP_ERR");
	close(info->tmp_fd);
	if (info->cmd_path == NULL)
		exit_perror("FILE_NAME_ERR"); // 명령어 에러 처리 필요
	info->cmd = get_cmd(info->cmd_path, cmd->cmd[0]);
	if (info->cmd == NULL)
		exit_perror("ERR_CMD"); // 명령어 에러 처리 필요
	if (execve(info->cmd, cmd->cmd, NULL) == -1)
		exit_perror("EXE_ERR");
}

void	parent_process(t_info *info)
{
	// close(info->tmp_fd);
	info->tmp_fd = dup(info->pipe_fd[0]);
	if (info->tmp_fd == -1)
		perror("FD_ERR");
	close(info->pipe_fd[0]);
	close(info->pipe_fd[1]);
}

void	dup_stdout(t_info *info, t_cmd *cmd)
{
	if (info->have_outfile == 1)
	{
		printf("outfile cmd\n");
		if (cmd->redir == NULL || cmd->redir->filename == NULL)
			return ;
		// info->outfile_fd = open(cmd->redir->filename, \
		// 	O_WRONLY | O_CREAT | O_TRUNC, 0644); // outfile 이름 받는 방법 수정 필요
		// if (info->outfile_fd == -1)
		// 	exit_perror(cmd->redir->filename);
		if (dup2(info->outfile_fd, STDOUT_FILENO) == -1)
			exit_perror("DUP_ERR");
		close(info->outfile_fd);
	}
	else if (cmd->next != NULL)
	{
		printf("not outfile cmd\n");
		if (dup2(info->pipe_fd[1], STDOUT_FILENO) == -1)
			perror("DUP_ERR");
	}
	close(info->pipe_fd[1]);
}

void	exit_perror(char *msg)
{
	perror(msg);
	exit(1);
}
