/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_term.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:38:54 by seoson            #+#    #+#             */
/*   Updated: 2023/11/07 12:54:53 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_termios(struct termios *old_term, struct termios *new_term)
{
	if (tcgetattr(STDIN_FILENO, old_term) == -1)
		return (-1);
	if (tcgetattr(STDIN_FILENO, new_term) == -1)
		return (-1);
	new_term->c_lflag = ~(ICANON);
	new_term->c_lflag = ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, new_term);
	set_signal();
	return (1);
}

int	reset_termios(struct termios *old_term)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, old_term) == -1)
		return (-1);
	return (1);
}
