/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:54:54 by seoson            #+#    #+#             */
/*   Updated: 2023/10/19 17:03:12 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int argc, char **argv, char **envp

// int	check_quote(char *line)
// {
// 	int	cnt;
	
// 	cnt = 0;
// 	return (cnt);
// }

int	check_white_space(char *line)
{
	int	index;

	index = 0;
	while (line[index])
	{
		if (line[index] >= 9 && line[index] <= 13)
			return (-1);
		if (line[index] == 32)
			return (-1);
		index++;
	}
	return (1);
}

int	check_available(char *line)
{
	if (check_white_space(line) == -1)
		return (-1);
	// check_first_pipe(line);
	return (1);
}

void	parse(char *line)
{
	int	index;

	if (check_available(line) == -1)
		return ;
	index = 0;
	while (line[index])
	{
		printf("%c\n", line[index]);
		index++;
	}
	return ;
}

void	print_picture(void)
{
	printf("  /\\       /\\ \n");
	printf(" /  \\\"\"\"\"\"/  \\ \n");
	printf("|  \\/\\\"\"\"/\\/  |\n");
	printf("`, <G>\\\"/<G> ,`\n");
	printf("====== Y ======\n");
	printf("  \\   -^-   /\n");
	printf("   \\       / \\__,\n");
	printf("  /  `````       \\______,\n");
	printf(" |    ```         \" \" \"  \\,\n");
	printf(" |     `           \" \"     \\\n");
	printf(" |            |     \"   \"   \\\n");
	printf(" |    _      /            \" |\n");
	printf(" | \" / \\ \"  /              \"|\n");
	printf(" |   | |   |\\__ _______\\   \"|\n");
	printf("/ -  | | -  \\ /   \"   \"   \" /\n");
	printf("\\___/   \\___/ \\____________/\n");
}

int main()
{
	struct termios	old_term;
	struct termios	new_term;
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
			parse(line);
		}
		free(line);
	}
	if (reset_termios(&old_term) == -1)
		return (-1);
}
