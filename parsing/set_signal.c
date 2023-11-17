/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:59:43 by seoson            #+#    #+#             */
/*   Updated: 2023/11/17 18:37:07 by seoson           ###   ########.fr       */
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
	//명령어를 실행할 때 fork를 하게 된다면 포크 바로 전에 시그널을 디폴트로 바꾼 다음 포크를 실행하고 부모 프로세스에서는 무시하도록 변경. 명령어 실행이 후 다음 입력값을 받도록 준비할 때 쉘에서의 동작으로 변경
	//cat, grep 등의 명령어중에 ctrl+c를 입력하면 종료는 되겠지만 ^C는 안뜬다.
}
