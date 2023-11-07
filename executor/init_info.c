/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 11:43:42 by sgo               #+#    #+#             */
/*   Updated: 2023/10/31 17:22:35 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	init_info(t_info *info, t_envp *envp, t_cmd *cmd)
{
	info->cmd_path = find_path(envp, "PATH");
	info->pipe_fd[0] = 0;
	info->pipe_fd[1] = 1;
	info->cmd_cnt = cmd_cnt(cmd);
	info->tmp_fd = 0;
	info->outfile_fd = 1;
	info->pid = 1;
	info->status = 0;
	info->have_outfile = 0;
}