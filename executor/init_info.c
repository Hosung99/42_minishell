/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 11:43:42 by sgo               #+#    #+#             */
/*   Updated: 2023/11/11 20:19:17 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	init_info(t_info *info, t_envp *envp, t_cmd *cmd)
{
	info->cmd_path = find_path(envp, "PATH");
	info->cmd = NULL;
	info->cmd_start = cmd;
	info->envp_start = envp;
	info->pipe_fd[0] = 0; // dup(stdin)으로 수정할 예정
	info->pipe_fd[1] = 0;
	info->cmd_cnt = cmd_cnt(cmd);
	info->tmp_fd = dup(STDIN_FILENO);
	info->outfile_fd = dup(STDOUT_FILENO);
	info->stdout_fd = dup(STDOUT_FILENO);
	info->pid = 1;
	info->status = 0;
	info->have_outfile = 0;
}