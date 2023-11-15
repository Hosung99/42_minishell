/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:54:54 by seoson            #+#    #+#             */
/*   Updated: 2023/11/14 19:08:21 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

int	check_first_char(char *line)
{
	int	line_index;

	line_index = 0;
	while (line[line_index] == ' ' || line[line_index] == '\t')
		line_index++;
	if (line[line_index] == '|')
	{
		printf("minishell: syntax error near unexpected token '|'\n");
		g_exit_status = 258;
		return (0);
	}
	return (1);
}

void	foo(void)
{
	system("leaks --list minishell");
}

int	main(int argc, char **argv, char **envp)
{
	// atexit(foo);
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
	update_shlvl(&envp_list);
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
			{
				executor(cmd, &envp_list);
				free_cmd(&cmd);
			}
		}
		free(line);
	}
	if (reset_termios(&old_term) == -1)
		return (-1);
	exit(1);
}
