/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 00:36:55 by sgo               #+#    #+#             */
/*   Updated: 2023/10/31 10:41:07 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	wait_all(t_info *info)
{
	int	count;

	count = 0;
	waitpid(info->pid, &info->status, 0);
	while (count < info->cmd_cnt - 1)
	{
		if (wait(0) == -1)
			exit(1);
		count++;
	}
}
