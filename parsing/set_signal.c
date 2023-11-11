/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:59:43 by seoson            #+#    #+#             */
/*   Updated: 2023/11/15 17:16:43 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	set_signal(char *str)
{
	if (ft_strncmp(str, "default", 7) == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (ft_strncmp(str, "ignore", 6) == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
	}
	//나중엔 자식프로세스에서 보내는 시그널에 따라 해당시그널이 처리되도록 if문으로 수정필요. 인자로 void대신 해당 signum을 받아서.
	//명령어를 실행할 때 fork를 하게 된다면 포크 바로 전에 시그널을 디폴트로 바꾼 다음 포크를 실행하고 부모 프로세스에서는 무시하도록 변경. 명령어 실행이 후 다음 입력값을 받도록 준비할 때 쉘에서의 동작으로 변경(해당 쉘에서 어케동작할지?).
	//cat, grep 등의 명령어중에 ctrl+c를 입력하면 종료는 되겠지만 ^C는 안뜬다.
}
