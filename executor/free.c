/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 01:11:15 by sgo               #+#    #+#             */
/*   Updated: 2023/11/14 19:01:47 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	free_info(t_info *info)
{
	free_str(info->cmd_path);
	ft_free(info->cmd);
	close(info->pipe_fd[0]);
	close(info->pipe_fd[1]);
	free_cmd(&info->cmd_start);
}

void	exit_free(t_info *info)
{
	free_info(info);
	exit(g_exit_status);
}

void	ft_free(void *ptr)
{
	if (ptr != NULL)
		free(ptr);
	ptr = NULL;
}
