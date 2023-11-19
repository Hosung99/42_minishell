/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 00:36:55 by sgo               #+#    #+#             */
/*   Updated: 2023/11/19 17:07:11 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	wait_all(void)
{
	int	i;
	int	status;
	int	signo;

	i = 0;
	while (wait(&status) != -1)
	{
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
	}
}
