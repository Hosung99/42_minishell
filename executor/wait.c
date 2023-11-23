/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 00:36:55 by sgo               #+#    #+#             */
/*   Updated: 2023/11/23 21:13:55 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	wait_all(t_cmd	*cmd)
{
	int	i;
	int	status;
	int	signo;

	i = 0;
	while (cmd)
	{
		waitpid(cmd->pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			signo = WTERMSIG(status);
			if (signo == SIGINT && i++ == 0)
				ft_putstr_fd("^C\n", STDERR_FILENO);
			else if (signo == SIGQUIT && i++ == 0)
			{
				ft_putstr_fd("^\\Quit: 3\n", STDERR_FILENO);
			}
			g_exit_status = 128 + signo;
		}
		else
			g_exit_status = WEXITSTATUS(status);
		cmd = cmd->next;
	}
}
