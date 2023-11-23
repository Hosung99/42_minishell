/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:18:12 by sgo               #+#    #+#             */
/*   Updated: 2023/11/23 16:19:04 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	child_process(t_cmd *cmd, t_info *info, t_envp *envp)
{
	char	**input_envp;

	if (!cmd->cmd || !cmd->cmd[0])
		exit_free(info);
	close(info->pipe_fd[0]);
	dup_stdout(info, cmd);
	if (is_builtin(cmd->cmd[0]))
	{
		builtin(cmd, info, envp);
		exit_free(info);
	}
	if (info->tmp_fd < 0)
		exit_free(info);
	if (dup2(info->tmp_fd, STDIN_FILENO) == -1)
		exit_perror("dup2", info);
	close(info->tmp_fd);
	if (info->cmd_path == NULL)
		ft_no_file_dir(cmd->cmd[0], info);
	info->cmd = get_cmd(info->cmd_path, cmd->cmd[0], info);
	if (info->cmd == NULL)
		ft_cmd_error(cmd->cmd[0]);
	input_envp = get_envp(envp);
	set_signal(CHI, CHI);
	if (execve(info->cmd, cmd->cmd, input_envp) == -1)
		exit_perror("execve", info);
}

void	parent_process(t_info *info)
{
	close(info->tmp_fd);
	info->tmp_fd = dup(info->pipe_fd[0]);
	if (info->tmp_fd == -1)
		ft_perror("dup");
	close(info->pipe_fd[0]);
	close(info->pipe_fd[1]);
}

void	dup_stdout(t_info *info, t_cmd *cmd)
{
	if (info->have_outfile == 1)
	{
		if (cmd->redir == NULL || cmd->redir->filename == NULL)
			return ;
		if (info->outfile_fd == -1)
			exit_free(info);
		if (dup2(info->outfile_fd, STDOUT_FILENO) == -1)
			exit_perror("dup2", info);
		close(info->outfile_fd);
		close(info->pipe_fd[1]);
	}
	else if (cmd->next != NULL)
	{
		if (dup2(info->pipe_fd[1], STDOUT_FILENO) == -1)
			ft_perror("dup2");
		close(info->pipe_fd[1]);
	}
}

void	dup_stdout_builtin(t_info *info, t_cmd *cmd)
{
	if (info->have_outfile == 1)
	{
		if (cmd->redir == NULL || cmd->redir->filename == NULL)
			return ;
		if (dup2(info->outfile_fd, STDOUT_FILENO) == -1)
			exit_perror("dup2", info);
		close(info->outfile_fd);
	}
}

void	exit_perror(char *msg, t_info *info)
{
	ft_perror(msg);
	free_info(info);
	exit(EXIT_FAILURE);
}
