/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 01:11:15 by sgo               #+#    #+#             */
/*   Updated: 2023/11/18 20:42:27 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	free_info(t_info *info)
{
	free_str(info->cmd_path);
	ft_free(info->cmd);
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
