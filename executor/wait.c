/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 00:36:55 by sgo               #+#    #+#             */
/*   Updated: 2023/11/18 21:11:05 by sgo              ###   ########.fr       */
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
		printf("status : %d\n", status);
		if (WIFSIGNALED(status))
		{
			signo = WTERMSIG(status);
			printf("signo : %d\n", signo);
			if (signo == SIGINT && i++ == 0)
				ft_putstr_fd("^C\n", STDERR_FILENO);
			else if (signo == SIGQUIT && i++ == 0)
			{
				printf("signo : %d\n", signo);
				ft_putstr_fd("^\\Quit: 3\n", STDERR_FILENO);
			}
			g_exit_status = 128 + signo;
		}
		else
			g_exit_status = WEXITSTATUS(status);
	}
}
