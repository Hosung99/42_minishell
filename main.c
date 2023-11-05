/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:54:54 by seoson            #+#    #+#             */
/*   Updated: 2023/11/05 19:17:43 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exit_status;

int	check_first_char(char *line)
{
	if (line[0] == '|')
	{
		printf("minishell: syntax error near unexpected token `%c'\n", line[0]);
		return (1);
	}
	return (-1);
}

int main(int argc, char **argv, char **envp)
{
	struct termios	old_term;
	struct termios	new_term;
	t_cmd			*cmd;
	t_envp			envp_list;
	char			*line;

	if (print_picture(argc, argv) == -1)
		return (-1);
	set_envp(envp, &envp_list);
	if (set_termios(&old_term, &new_term) == -1)
		return (-1);
	set_signal();
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line != '\0' && check_first_char(line))
		{
			add_history(line);
			parse(line, &cmd, &envp_list);
		}
		free(line);
	}
	if (reset_termios(&old_term) == -1)
		return (-1);
}
