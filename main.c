/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:54:54 by seoson            #+#    #+#             */
/*   Updated: 2023/11/21 07:07:27 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

int	main(int argc, char **argv, char **envp)
{
	t_termios		term;
	t_cmd			*cmd;
	t_envp			envp_list;
	char			*line;

	if (print_picture(argc, argv) == -1)
		return (-1);
	set_init(envp, &envp_list, &term);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line != '\0' && check_first_char(line))
		{
			add_history(line);
			if (parse(line, &cmd, &envp_list) == -1)
				free_cmd(&cmd);
			else
				executor(cmd, &envp_list);
		}
		free(line);
	}
	reset_termios(&term);
	exit(EXIT_SUCCESS);
}
