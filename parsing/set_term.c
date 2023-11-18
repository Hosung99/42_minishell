/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_term.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:38:54 by seoson            #+#    #+#             */
/*   Updated: 2023/11/18 17:45:08 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_termios(t_termios *term)
{
	tcgetattr(STDIN_FILENO, &term->old_term);
	tcgetattr(STDIN_FILENO, &term->new_term);
	term->new_term.c_lflag = ~(ICANON);
	term->new_term.c_lflag = ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term->new_term);
	set_signal(TER, TER);
}

void	reset_termios(t_termios *term)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &term->old_term);
	set_signal(DEF, DEF);
}
