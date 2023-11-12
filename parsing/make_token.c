/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:09:15 by seoson            #+#    #+#             */
/*   Updated: 2023/11/12 17:01:36 by seoson           ###   ########.fr       */
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
	if (fin_index == space_index && str[fin_index] == '\0')
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

// void	make_cmd_token(char *str, t_token *token_header,
// 	int *curr_index, int *before_index)
// {
// 	t_token	*new_token;

// 	if (*curr_index != 0 && (((str[*curr_index - 1] == ' ' || \
// 		str[*curr_index - 1] == '\t') && (str[*curr_index] == ' ' || \
// 			str[*curr_index] == '\t')) || ((str[*curr_index - 1] == '<' || \
// 				str[*curr_index - 1] == '>' || str[*curr_index - 1] == '\'' || \
// 					str[*curr_index - 1] == '"') && (str[*curr_index] == '\0' || \
// 						str[*curr_index] == ' ' || str[*curr_index] == '\t'))))
// 		return ;
// 	if (*curr_index != 0 && ((str[*curr_index] == '<' || str[*curr_index] == '>') \
// 		&& (str[*curr_index - 1] == ' ' || str[*curr_index - 1] == '\t') \
// 			&& !(str[*curr_index + 1] == '\0')))
// 		return ;
// 	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
// 	if (str[*curr_index + 1] == '\0')
// 		new_token->str = ft_split_index(str, *before_index, *curr_index);
// 	else
// 		new_token->str = ft_split_index(str, *before_index, *curr_index - 1);
// 	new_token->type = set_token_type(new_token->str);
// 	new_token->next = NULL;
// 	set_token_position(token_header, new_token);
// 	*before_index = *curr_index + 1;
// 	*curr_index = *curr_index + 1;
// }

// void	malloc_redir_token(char *str, t_token **new_token,
// 	int *cur_index, int redir_cnt)
// {
// 	(*new_token)->str = (char *)malloc(sizeof(char) * redir_cnt + 1);
// 	if (!(*new_token)->str)
// 		return ;
// 	if (redir_cnt == 1)
// 	{
// 		(*new_token)->str[0] = str[*cur_index];
// 		(*new_token)->str[1] = '\0';
// 	}
// 	else if (redir_cnt == 2)
// 	{
// 		(*new_token)->str[0] = str[*cur_index];
// 		(*new_token)->str[1] = str[*cur_index + 1];
// 		(*new_token)->str[2] = '\0';
// 		*cur_index = *cur_index + 1;
// 	}
// 	(*new_token)->type = set_token_type((*new_token)->str);
// 	(*new_token)->next = NULL;
// }

// void	make_redir_token(char *str, t_token *token_header, int *cur_index, int *before_index)
// {
// 	t_token	*new_token;

// 	new_token = (t_token *)malloc(sizeof(t_token));
// 	if (!new_token)
// 		return ;
// 	if (*cur_index != *before_index)
// 		make_cmd_token(str, token_header, cur_index, before_index);
// 	if (str[*cur_index + 1] == '>' || str[*cur_index + 1] == '<')
// 		malloc_redir_token(str, &new_token, cur_index, 2);
// 	else
// 		malloc_redir_token(str, &new_token, cur_index, 1);
// 	set_token_position(token_header, new_token);
// 	*before_index = *cur_index + 1;
// }

// int	ft_is_space(char *str, int *curr_index)
// {
// 	int	index;

// 	index = *curr_index;
// 	while (str[index])
// 	{
// 		if (str[index] == ' ' || str[index] == '\t')
// 			return (1);
// 		index++;
// 	}
// 	return (-1);
// }

// void	set_curr_index(char *str, int *curr_index)
// {
// 	int	str_index;

// 	str_index = *curr_index;
// 	while (str_index < 0 && str[str_index])
// 	{
// 		if (str[str_index] == ' ' || str[str_index] == '\t' || str[str_index] == '<' || str[str_index] == '>')
// 			break;
// 		str_index--;
// 	}
// 	if (str_index == -1)
// 		*curr_index = 0;
// 	else
// 		*curr_index = str_index;
// }

// int	check_quote_cnt(char *str, int *curr_index)
// {
// 	int	quote_cnt;
// 	int	str_index;

// 	quote_cnt = 0;
// 	str_index = 0;
// 	while (str[str_index])
// 	{
// 		if (str[*curr_index] == str[str_index])
// 			quote_cnt++;
// 		str_index++;
// 	}
// 	return (quote_cnt);
// }

// int	check_quote_index(char *str, int *curr_index)
// {
// 	int	quote_cnt;
// 	int	str_index;

// 	quote_cnt = check_quote_cnt(str, curr_index);
// 	str_index = *curr_index + 1;
// 	while (str && str[str_index])
// 	{
// 		if (str[*curr_index] == str[str_index])
// 			quote_cnt--;
// 		if (quote_cnt == 1 && (str[str_index] == ' ' || str[str_index] == '\t' || str[str_index] == '<' || str[str_index] == '>'))
// 			break ;
// 		str_index++;
// 	}
// 	set_curr_index(str, curr_index);
// 	if (ft_is_space(str, curr_index) == 1)
// 		return (str_index);
// 	return ((int) ft_strlen(str));
// }

// void	make_quote_token(char *str, t_token *token_header, int *curr_index, int *before_index)
// {
// 	t_token	*new_token;
// 	char	quote_type;

// 	new_token = (t_token *)malloc(sizeof(t_token));
// 	quote_type = str[*curr_index];
// 	if (*before_index != *curr_index && str[*curr_index - 1] != ' ' && str[*curr_index - 1] != '\t')
// 	{
// 		make_cmd_token(str, token_header, curr_index, before_index);
// 		*curr_index = *curr_index - 1;
// 	}
// 	if (str[*curr_index] != '\0')
// 		*curr_index = *curr_index + 1;
// 	if (str[*curr_index] == quote_type)
// 	{
// 		free(new_token);
// 		*before_index = *curr_index + 1;
// 		return ;
// 	}
// 	new_token->str = NULL;
// 	while (str[*curr_index] && str[*curr_index] != quote_type)
// 	{
// 		new_token->str = ft_strjoin_char(new_token->str, str[*curr_index]);
// 		*curr_index = *curr_index + 1;
// 	}
// 	if (str[*curr_index] == '\0')
// 	{
// 		free(new_token->str);
// 		free(new_token);
// 		return ;
// 	}
// 	new_token->type = TOKEN_WORD;
// 	new_token->next = NULL;
// 	set_token_position(token_header, new_token);
// 	*before_index = *curr_index + 1;
// }
