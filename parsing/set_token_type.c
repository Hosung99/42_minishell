/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:26:44 by seoson            #+#    #+#             */
/*   Updated: 2023/10/25 17:32:17 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static int check_token_type(char next_char, char second_char, \
// 	int token_type_single, int token_type_double)
// {
// 	if (next_char == '\0')
// 		return token_type_single;
// 	else if (next_char == '>' && second_char == '\0')
// 		return token_type_double;
// 	else if (next_char == '<' && second_char == '\0')
// 		return token_type_double;
// 	else
// 		return token_redir_with_str;
// }

int	set_token_type(char *str)
{
	int	index;

	index = 0;
	while (str && str[index])
	{
		if (str[index] == '-')
			return token_option;
		if (str[index] == '>') 
		{
			return token_read_redir;
			// return (check_token_type(str[index + 1], str[index + 2],
			// 	token_write_redir,token_append_redir));
		}
		else if (str[index] == '<') 
		{
			return token_write_redir;
			// return (check_token_type(str[index + 1], str[index + 2],
			// 	token_read_redir ,token_heredoc));
		}
		index++;
	}
	return token_cmd;
}
