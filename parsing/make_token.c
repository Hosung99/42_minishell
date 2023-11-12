/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:09:15 by seoson            #+#    #+#             */
/*   Updated: 2023/11/12 18:19:05 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_strjoin_char(char *str, char c)
{
	char	*new_str;
	int		str_index;

	str_index = 0;
	if (str != NULL)
		new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
	else
		new_str = (char *)malloc(sizeof(char) * 2);
	while (str && str[str_index])
	{
		new_str[str_index] = str[str_index];
		str_index++;
	}
	new_str[str_index++] = c;
	new_str[str_index] = '\0';
	free(str);
	return (new_str);
}

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
		return (1);
	return (0);
}


int	make_cmd_token(char *str, t_token *token_header, int curr_index)
{
	t_token	*new_token;
	int		space_index;
	int		fin_index;

	space_index = curr_index + 1;
	while (str[space_index] && ft_is_space(str[space_index]) == 1)
		space_index++;
	fin_index = space_index;
	while (str[fin_index] && isMetachar(str[fin_index]) == 0)
		fin_index++;
	if ((fin_index == space_index && str[fin_index] == '\0') || isMetachar(str[fin_index]) == 1)
		return (fin_index);
	else if (fin_index == space_index)
		return (fin_index + 1);
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
	if (str[space_index] == '<' || str[space_index] == '>')
		space_index++;
	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	new_token->str = ft_substr(str, curr_index, space_index - curr_index);
	new_token->type = set_token_type(new_token->str);
	set_token_position(token_header, new_token);
	while (str[space_index] && ft_is_space(str[space_index]) == 1)
		space_index++;
	return (space_index);
}

int	make_quote_token(char *str, t_token *token_header, int curr_index)
{
	t_token	*new_token;
	char	quote_type;

	new_token = (t_token *)malloc(sizeof(t_token));
	quote_type = str[curr_index];
	if (str[curr_index] != '\0')
		curr_index = curr_index + 1;
	new_token->str = NULL;
	while (str[curr_index] && str[curr_index] != quote_type)
	{
		new_token->str = ft_strjoin_char(new_token->str, str[curr_index]);
		curr_index = curr_index + 1;
	}
	if (str[curr_index] == '\0')
	{
		free(new_token->str);
		free(new_token);
		return (1);
	}
	new_token->type = TOKEN_WORD;
	new_token->next = NULL;
	set_token_position(token_header, new_token);
	curr_index = curr_index + 1;
	return (1);
}
