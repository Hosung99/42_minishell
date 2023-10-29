/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:09:15 by seoson            #+#    #+#             */
/*   Updated: 2023/10/28 15:58:42 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_token_position(t_token *token_header, t_token *new_token, int *before_index)
{
	if (*before_index == 0)
		token_header->next = new_token;
	else
	{
		while (token_header->next != NULL)
			token_header = token_header->next;
		token_header->next = new_token;
	}
}

void	make_cmd_token(char *str, t_token *token_header,
	int *curr_index, int *before_index)
{
	t_token	*new_token;

	printf("curr_index : %d\n", *curr_index);
	if (*curr_index != 0 && (str[*curr_index - 1] == ' ' || str[*curr_index - 1] == '\t' || str[*curr_index] == '>' || str[*curr_index] == '<'))
		return ;
	if (str[*curr_index + 1] == '\0')
		*curr_index = *curr_index + 1;
	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->str = ft_split_index(str, *before_index, *curr_index - 1);
	printf("new_token->str1 : %s\n", new_token->str);
	new_token->type = set_token_type(new_token->str);
	new_token->next = NULL;
	set_token_position(token_header, new_token, before_index);
	*before_index = *curr_index + 1;
}

void	malloc_redir_token(char *str, t_token **new_token,
	int *cur_index, int redir_cnt)
{
	(*new_token)->str = (char *)malloc(sizeof(char) * redir_cnt + 1);
	if (!(*new_token)->str)
		return ;
	if (redir_cnt == 1)
	{
		(*new_token)->str[0] = str[*cur_index];
		(*new_token)->str[1] = '\0';
	}
	else if (redir_cnt == 2)
	{
		(*new_token)->str[0] = str[*cur_index];
		(*new_token)->str[1] = str[*cur_index + 1];
		(*new_token)->str[2] = '\0';
		*cur_index = *cur_index + 1;
	}
	(*new_token)->type = set_token_type((*new_token)->str);
	(*new_token)->next = NULL;
}

void	make_redir_token(char *str, t_token *token_header, int *cur_index, int *before_index)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return ;
	if (*cur_index != *before_index)
		make_cmd_token(str, token_header, cur_index, before_index);
	if (str[*cur_index + 1] == '>' || str[*cur_index + 1] == '<')
		malloc_redir_token(str, &new_token, cur_index, 2);
	else
		malloc_redir_token(str, &new_token, cur_index, 1);
	printf("new_token->str2 : %s\n", new_token->str);
	set_token_position(token_header, new_token, before_index);
	*before_index = *cur_index + 1;
}

int	ft_is_space(char *str, int *curr_index)
{
	int	index;

	index = *curr_index;
	while (str[index])
	{
		if (str[index] == ' ' || str[index] == '\t')
			return (1);
		index++;
	}
	return (-1);
}

void	set_curr_index(char *str, int *curr_index)
{
	int	str_index;

	str_index = *curr_index;
	while (str[str_index])
	{
		printf("str_index : %d\n", str_index);
		if (str[str_index] != ' ' && str[str_index] != '\t')
		{
			*curr_index = str_index;
			return ;
		}
		str_index--;
	}
}

int	check_quote_cnt(char *str, int *curr_index)
{
	int	quote_cnt;
	int	str_index;

	quote_cnt = 0;
	str_index = 0;
	while (str[str_index])
	{
		if (str[*curr_index] == str[str_index])
			quote_cnt++;
		str_index++;
	}
	return (quote_cnt);
}

int	check_quote_index(char *str, int *curr_index)
{
	int	quote_cnt;
	int	str_index;
	
	quote_cnt = check_quote_cnt(str, curr_index);
	str_index = *curr_index + 1;
	while (str[str_index] && str[str_index])
	{
		if (str[*curr_index] == str[str_index])
			quote_cnt--;
		if (quote_cnt == 1)
			break ;
		str_index++;
	}
	set_curr_index(str, curr_index);
	if (ft_is_space(str, curr_index) == 1)
		return (str_index);
	return ((int)ft_strlen(str));
}

void	make_quote_token(char *str, t_token *token_header, int *curr_index, int *before_index)
{
	t_token	*new_token;
	int		end_index;
	int		str_index;

	new_token = (t_token *)malloc(sizeof(t_token));
	end_index = check_quote_index(str, curr_index);
	str_index = 0;
	if (!new_token)
		return ;
	if (end_index > *curr_index + 1)
		new_token->str = (char *)malloc(sizeof(char) * (end_index - *curr_index + 1));
	if (!new_token->str)
		return ;
	while (str_index <= end_index)
	{
		new_token->str[str_index++] = str[*curr_index];
		*curr_index = *curr_index + 1;
	}
	new_token->str[str_index] = '\0';
	printf("new_token->str3 : %s\n", new_token->str);
	new_token->type = set_token_type(new_token->str);
	new_token->next = NULL;
	set_token_position(token_header, new_token, before_index);
	*before_index = *curr_index;
}
