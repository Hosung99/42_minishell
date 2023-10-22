/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_term.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:38:54 by seoson            #+#    #+#             */
/*   Updated: 2023/10/21 16:46:21 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_termios(struct termios *old_term, struct termios *new_term)
{
	if (tcgetattr(STDIN_FILENO, old_term) == -1)
		return (-1);
	if (tcgetattr(STDIN_FILENO, new_term) == -1)
		return (-1);
	new_term->c_lflag = ~(ICANON); //noncanonical mode작동.
	new_term->c_lflag = ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, new_term);
	return (1);
}

int	reset_termios(struct termios *old_term)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, old_term) == -1)
		return (-1);
	return (1);
}