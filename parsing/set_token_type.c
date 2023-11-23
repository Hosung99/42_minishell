/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:26:44 by seoson            #+#    #+#             */
/*   Updated: 2023/11/23 15:11:15 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	return_quote_flag(int quote_flag)
{
	if (quote_flag == 1)
		return (FAILURE);
	else
		return (SUCCESS);
}

static int	check_quote_flag(int quote_flag, int temp_index, int str_index)
{
	if (quote_flag == 0 && temp_index == str_index)
		return (SUCCESS);
	else if (quote_flag == 1 && temp_index == str_index)
		return (FAILURE);
	return (0);
}

int	check_quote(char *str, int str_index)
{
	char	quote_temp;
	int		temp_index;
	int		quote_flag;

	quote_flag = 0;
	temp_index = -1;
	while (++temp_index < str_index)
	{
		if (quote_flag == 0 && str[temp_index] == '\'')
			quote_flag = 1;
		else if (quote_flag == 1 && str[temp_index] == '\'')
			quote_flag = 0;
		if (str[temp_index] == '\"' || str[temp_index] == '\'')
		{
			quote_temp = str[temp_index++];
			while (str[temp_index] != quote_temp && temp_index < str_index)
				temp_index++;
			if (check_quote_flag(quote_flag, temp_index, str_index))
				return (check_quote_flag(quote_flag, temp_index, str_index));
			if (str[temp_index] == '\'')
				quote_flag = 0;
		}
	}
	return (return_quote_flag(quote_flag));
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
