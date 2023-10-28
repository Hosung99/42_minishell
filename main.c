/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:54:54 by seoson            #+#    #+#             */
/*   Updated: 2023/10/26 15:31:06 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int argc, char **argv, char **envp

int main()
{
	struct termios	old_term;
	struct termios	new_term;
	t_cmd			cmd;
	char			*line;

	print_picture();
	if (set_termios(&old_term, &new_term) == -1)
		return (-1);
	set_signal();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line != '\0')
		{
			add_history(line);
			parse(line, &cmd);
		}
		free(line);
	}
	if (reset_termios(&old_term) == -1)
		return (-1);
}
