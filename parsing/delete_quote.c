/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:26:14 by seoson            #+#    #+#             */
/*   Updated: 2023/11/21 20:52:17 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	ft_is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (c);
	return (0);
}

static size_t	ft_quote_str_len(char *str)
{
	size_t	str_index;

	str_index = 0;
	while (str && str[str_index])
	{
		if (str[str_index] == '\'' || str[str_index] == '"')
			return (str_index);
		str_index++;
	}
	return (str_index);
}

void	check_quote_type(t_token *token, char **new_str, int *str_index)
{
	char	quote_type;

	quote_type = token->str[*str_index];
	*str_index = *str_index + 1;
	while (token->str[*str_index] && quote_type != token->str[*str_index])
	{
		*new_str = ft_strjoin_char(*new_str, token->str[*str_index]);
		if (*new_str == NULL)
			exit(EXIT_FAILURE);
		*str_index = *str_index + 1;
	}
}

void	delete_quote(t_token *token)
{
	int		str_index;
	char	*new_str;

	str_index = 0;
	if (ft_strlen(token->str) == ft_quote_str_len(token->str))
		return ;
	new_str = ft_strdup("");
	while (token->str && token->str[str_index])
	{
		if (ft_is_quote(token->str[str_index]) != 0)
			check_quote_type(token, &new_str, &str_index);
		else
			new_str = ft_strjoin_char(new_str, token->str[str_index]);
		if (new_str == NULL)
			exit(EXIT_FAILURE);
		if (token->str[str_index] != '\0')
			str_index++;
	}
	free(token->str);
	token->str = new_str;
}
