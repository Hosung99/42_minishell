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

void	wait_all(t_info *info)
{
	int	count;
	int	status;

	count = 0;
	waitpid(info->pid, &status, 0);
	g_exit_status = WEXITSTATUS(status);
	while (count < info->cmd_cnt - 1)
	{
		if (wait(0) == -1)
			exit_free(info);
		count++;
	}
}
