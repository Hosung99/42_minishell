/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:59:43 by seoson            #+#    #+#             */
/*   Updated: 2023/11/18 17:45:20 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_handler(int signo)
{
	(void)signo;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	exit(1);
}

void	sig_handler(int signo)
{
	if (signo == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (signo == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	set_signal(int sig_int, int sig_quit)
{
	if (sig_int == IGN)
		signal(SIGINT, SIG_IGN);
	else if (sig_int == DEF)
		signal(SIGINT, SIG_DFL);
	else if (sig_int == TER)
		signal(SIGINT, sig_handler);
	else if (sig_int == CHI)
		signal(SIGINT, child_handler);
	if (sig_quit == IGN)
		signal(SIGQUIT, SIG_IGN);
	else if (sig_quit == DEF)
		signal(SIGQUIT, SIG_DFL);
	else if (sig_quit == TER)
		signal(SIGQUIT, sig_handler);
}
