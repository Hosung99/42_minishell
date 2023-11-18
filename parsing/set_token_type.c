/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:26:44 by seoson            #+#    #+#             */
/*   Updated: 2023/11/18 17:25:29 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_in_d_quote(char *str, int str_index)
{
	while (str && str[str_index])
	{
		if (str[str_index] == '"')
			return (1);
		else if (str[str_index] == '\'')
			return (0);
		if (str_index == 0)
			break ;
		str_index--;
	}
	return (1);
}

int	check_in_quote(char *str, int str_index)
{
	while (str && str[str_index])
	{
		if (str[str_index] == '\'' || str[str_index] == '\"')
			return (1);
		if (str_index == 0)
			return (0);
		str_index--;
	}
	return (0);
}

int	set_token_type(char *str)
{
	int	str_index;

	str_index = 0;
	while (str && str[str_index])
	{
		if (str[str_index] == '>')
		{
			if (check_in_quote(str, str_index) == 0)
				return (TOKEN_READ_REDIR);
		}
		else if (str[str_index] == '<')
		{
			if (check_in_quote(str, str_index) == 0)
				return (TOKEN_WRITE_REDIR);
		}
		str_index++;
	}
	return (TOKEN_WORD);
}
