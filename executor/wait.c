/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 00:36:55 by sgo               #+#    #+#             */
/*   Updated: 2023/11/14 19:12:36 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

// extern int	g_exit_status;

void	wait_all(t_info *info)
{
	int	count;

	count = 0;
	waitpid(info->pid, NULL, 0);
	while (count < info->cmd_cnt - 1)
	{
		if (wait(0) == -1)
			exit_free(info);
		count++;
	}
}
