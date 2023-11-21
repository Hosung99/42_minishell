/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:26:44 by seoson            #+#    #+#             */
/*   Updated: 2023/11/21 20:42:28 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quote(char *str, int str_index)
{
	char	quote_type;
	int		d_quote_cnt;
	int		s_quote_cnt;

	d_quote_cnt = 0;
	s_quote_cnt = 0;
	while (str[str_index])
	{
		if (str[str_index] == '\'')
			s_quote_cnt++;
		if (str[str_index] == '"')
			d_quote_cnt++;
		if (str[str_index] == '\'' || str[str_index] == '"')
			quote_type = str[str_index];
		if (str_index == 0)
			break ;
		str_index--;
	}
	if (d_quote_cnt % 2 == 0 && s_quote_cnt % 2 == 0)
		return (SUCCESS);
	if (d_quote_cnt % 2 == 1 && quote_type == '"')
		return (SUCCESS);
	return (FAILURE);
}

int	check_in_quote(char *str, int str_index)
{
	while (str && str[str_index])
	{
		if (str[str_index] == '\'' || str[str_index] == '\"')
			return (SUCCESS);
		if (str_index == 0)
			return (FAILURE);
		str_index--;
	}
	return (FAILURE);
}

int	set_token_type(char *str)
{
	int	str_index;

	str_index = 0;
	while (str && str[str_index])
	{
		if (str[str_index] == '>')
		{
			if (check_in_quote(str, str_index) == FAILURE)
				return (TOKEN_READ_REDIR);
		}
		else if (str[str_index] == '<')
		{
			if (check_in_quote(str, str_index) == FAILURE)
				return (TOKEN_WRITE_REDIR);
		}
		str_index++;
	}
	return (TOKEN_WORD);
}
