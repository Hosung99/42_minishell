/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:59:15 by seoson            #+#    #+#             */
/*   Updated: 2023/10/31 16:36:54 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	delete_quote(t_token *token, char str)
{
	int	str_index;
	int	quote_cnt;

	str_index = 0;
	quote_cnt = 0;
	while (token->str[str_index])
	{
		if (token->str[str_index] == str)
			quote_cnt++;
		str_index++;
	}
	// if (quote_cnt % 4 == 0) //4개일때 ''"'' 에러나도록 수정필요.
	// 	return (-1);
	str_index = 0;
	while (token->str[str_index])
	{
		if (token->str[str_index] == str)
		{
			token->str = ft_strtrim_index(token->str, str);
			break;
		}
		str_index++;
	}
	return (1);
}

void	check_envp(t_token *token, int *str_index, t_envp *envp_list)
{
	int		temp_index;
	char	*envp_key;
	(void)envp_list;

	temp_index = *str_index;
	while (token->str[temp_index])
	{
		if (token->str[temp_index] == ' ' || token->str[temp_index] == '\t' \
			|| token->str[temp_index] == '$' || token->str[temp_index] == '\"')
			break;
		temp_index++;
	}
	envp_key = ft_search_envp_key(envp_list, ft_split_index(token->str, *str_index + 1, temp_index - 1));
	printf("envp key : %s\n", envp_key);
}

int	check_big_quote(t_token *token, int str_index, t_envp *envp_list)
{
	int	quote_cnt;
	int	quote_index;

	quote_cnt = 0;
	quote_index = 0;
	while(token->str[quote_index])
	{
		if (token->str[quote_index] == '\"')
			quote_cnt++;
		quote_index++;
	}
	if (quote_cnt % 2 != 0)
		return (-1);
	while(token->str[str_index] != '\"')
	{
		if (token->str[str_index] == '\0')
			return (-1);
		if (token->str[str_index] == '$')
			check_envp(token, &str_index, envp_list);
		str_index++;
	}
	if (delete_quote(token, '"') == -1)
		return (-1);
	return (1);
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
	if (delete_quote(token, '\'') == -1)
		return (-1); 
	return (1);
}

int	check_quote(t_token *token, t_envp *envp_list)
{
	char	*str;
	int	str_index;

	str = token->str;
	str_index = 0;
	while (str && str[str_index])
	{
		if (str[str_index] == '"')
		{
			if (check_big_quote(token, str_index, envp_list) == -1)
				return (-1);
			break;
		}
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

int	set_quote(t_token *token_header, t_envp *envp_list)
{
	while (token_header)
	{
		printf("before: token_header->str : %s\n", token_header->str);
		if (check_quote(token_header, envp_list) == -1)
			return (-1);
		printf("after: token_header->str : %s\n", token_header->str);
		token_header = token_header->next;
	}
	return (1);
}