/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 17:09:15 by seoson            #+#    #+#             */
/*   Updated: 2023/10/25 22:31:50 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	make_cmd_token(char *str, t_token *token_header,
	int *cur_index, int *before_index)
{
	t_token	*new_token;

	if (str[*cur_index + 1] == '\0')
		*cur_index = *cur_index + 1;
	else if (str[*cur_index - 1] == '>' || str[*cur_index - 1] == '<' || str[*cur_index - 1] == ' ')
		return ;
	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return ;
	new_token->str = ft_split_index(str, *before_index, *cur_index - 1);
	new_token->type = set_token_type(new_token->str);
	printf("new_token->str1 :%s type :%d\n", new_token->str, new_token->type);
	new_token->next = NULL;
	*before_index = *cur_index + 1;
	if (*before_index == 0)
		token_header->next = new_token;
	else
	{
		while (token_header->next != NULL)
			token_header = token_header->next;
		token_header->next = new_token;
	}
}

void	malloc_redir_token(char *str, t_token **new_token,
	int *cur_index, int *before_index, int redir_cnt)
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
	*before_index = *cur_index + 1;
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
		malloc_redir_token(str, &new_token, cur_index, before_index, 2);
	else
		malloc_redir_token(str, &new_token, cur_index, before_index, 1);
	printf("new_token->str2 : %s type :%d\n", new_token->str, new_token->type);
	if (*before_index == 0)
		token_header->next = new_token;
	else
	{
		while (token_header->next != NULL)
			token_header = token_header->next;
		token_header->next = new_token;
	}
}
