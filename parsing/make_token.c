/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:09:15 by seoson            #+#    #+#             */
/*   Updated: 2023/11/23 16:15:33 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_token_position(t_token *token_header, t_token *new_token)
{
	t_token	*token_header_temp;

	token_header_temp = token_header;
	if (token_header->next == NULL)
		token_header->next = new_token;
	else
	{
		while (token_header && token_header_temp->next != NULL)
			token_header_temp = token_header_temp->next;
		token_header_temp->next = new_token;
	}
}

int	ft_is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (SUCCESS);
	return (FAILURE);
}

int	make_cmd_token(char *str, t_token *token_header, int curr_index)
{
	t_token	*new_token;
	int		space_index;
	int		fin_index;

	space_index = curr_index + 1;
	while (str[space_index] && ft_is_space(str[space_index]) == SUCCESS)
		space_index++;
	if (is_quote(str[space_index]) == SUCCESS)
		return (space_index);
	fin_index = space_index;
	while (str[fin_index] && is_metachar(str[fin_index]) == FAILURE)
		fin_index++;
	if (fin_index == space_index)
		return (fin_index);
	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	new_token->str = ft_substr(str, space_index, fin_index - space_index);
	new_token->type = set_token_type(new_token->str);
	set_token_position(token_header, new_token);
	return (fin_index);
}

int	make_redir_token(char *str, t_token *token_header, int curr_index)
{
	t_token	*new_token;
	int		space_index;

	space_index = curr_index + 1;
	if (str[space_index] == str[curr_index])
		space_index++;
	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	new_token->str = ft_substr(str, curr_index, space_index - curr_index);
	new_token->type = set_token_type(new_token->str);
	set_token_position(token_header, new_token);
	while (str[space_index] && ft_is_space(str[space_index]) == SUCCESS)
		space_index++;
	return (space_index);
}
