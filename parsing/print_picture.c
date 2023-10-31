/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_picture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 16:50:37 by seoson            #+#    #+#             */
/*   Updated: 2023/10/31 14:29:23 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_picture(int argc, char **argv)
{
	if (argc != 1)
		return (-1);
	(void)argv;
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
	printf("Hello World!\n\n");
	return (1);
}
