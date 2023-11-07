/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:26:44 by seoson            #+#    #+#             */
/*   Updated: 2023/11/07 13:04:52 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_token_type(char next_char, char second_char, \
	int token_type_single, int token_type_double)
{
	if (next_char == '\0')
		return (token_type_single);
	else if (next_char == '>' && second_char == '\0')
		return (token_type_double);
	else if (next_char == '<' && second_char == '\0')
		return (token_type_double);
	else
		return (token_type_single);
}

int	set_token_type(char *str)
{
	int	index;

	index = 0;
	while (str && str[index])
	{
		if (str[index] == '-')
			return (TOKEN_WORD);
		if (str[index] == '>')
		{
			return (TOKEN_READ_REDIR);
			return (check_token_type(str[index + 1], str[index + 2], \
				TOKEN_WRITE_REDIR, TOKEN_APPEND_REDIR));
		}
		else if (str[index] == '<')
		{
			return (TOKEN_WRITE_REDIR);
			return (check_token_type(str[index + 1], str[index + 2], \
				TOKEN_READ_REDIR, TOKEN_HEREDOC));
		}
		index++;
	}
	return (TOKEN_WORD);
}
