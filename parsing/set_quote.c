/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:59:15 by seoson            #+#    #+#             */
/*   Updated: 2023/10/29 15:01:22 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// int	check_big_quote(t_token *token, int *str_index)
// {
// 	return (1);
// }

void	delete_small_quote(t_token *token)
{
	int	str_index;

	str_index = 0;
	while (token->str[str_index])
	{
		if (token->str[str_index] == '\'')
		{
			token->str = ft_strtrim_index(token->str, '\'');
			break;
		}
		str_index++;
	}
}

int	check_small_quote(t_token *token, int str_index)
{
	int	quote_cnt;
	int	quote_index;

	quote_cnt = 0;
	quote_index = 0;
	while(token->str[quote_index])
	{
		if (token->str[quote_index] == '\'')
			quote_cnt++;
		quote_index++;
	}
	if (quote_cnt % 2 != 0)
		return (-1);
	while(token->str[str_index] != '\'')
	{
		if (token->str[str_index] == '\0')
			return (-1);
		(str_index)++;
	}
	token->str = ft_strtrim(token->str, "\'");
	delete_small_quote(token);
	return (1);
}

int	check_quote(t_token *token)
{
	char	*str;
	int	str_index;

	str = token->str;
	str_index = 0;
	while (str && str[str_index])
	{
		// if (str[str_index] == '"')
		// {
		// 	if (check_big_quote(token, &str_index) == -1)
		// 		return (-1);
		// 	break;
		// }
		// else 
		if (str[str_index] == '\'')
		{
			if (check_small_quote(token, str_index) == -1)
				return (-1);
			break;
		}
		str_index++;
	}
	return (1);
}

int	set_quote(t_token *token_header)
{
	while (token_header)
	{
		printf("before: token_header->str : %s\n", token_header->str);
		if (check_quote(token_header) == -1)
			return (-1);
		printf("after: token_header->str : %s\n", token_header->str);
		token_header = token_header->next;
	}
	return (1);
}