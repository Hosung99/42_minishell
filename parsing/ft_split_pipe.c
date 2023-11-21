/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:41:05 by seoson            #+#    #+#             */
/*   Updated: 2023/11/21 20:50:01 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_word(char *str)
{
	int		word_cnt;
	int		str_index;
	int		quote_flag;

	str_index = 0;
	word_cnt = 0;
	quote_flag = 0;
	while (str && str[str_index])
	{
		if (quote_flag == 1 && (str[str_index] == '"' \
			|| str[str_index] == '\''))
			quote_flag = 0;
		else if (quote_flag == 0 && \
			(str[str_index] == '"' || str[str_index] == '\''))
			quote_flag = 1;
		if (quote_flag == 0 && str[str_index] == '|')
			word_cnt++;
		str_index++;
	}
	return (word_cnt);
}

static int	len_word(char	*str)
{
	int		word_len;
	int		quote_flag;

	word_len = 0;
	quote_flag = 0;
	while (*str)
	{
		if (quote_flag == 1 && (*str == '"' \
			|| *str == '\''))
			quote_flag = 0;
		else if (quote_flag == 0 && \
			(*str == '"' || *str == '\''))
			quote_flag = 1;
		if (quote_flag == 0 && *str == '|')
			break ;
		str++;
		word_len++;
	}
	return (word_len);
}

static char	**free_malloc(char **str, int i)
{
	while (i)
		free(str[--i]);
	free(str);
	return (0);
}

static	void	set_string(char **str, char **s, \
		int word_len)
{
	int	str_index;

	str_index = 0;
	while (str_index < word_len)
	{
		(*str)[str_index++] = **s;
		*s = *s + 1;
	}
	(*str)[str_index] = 0;
}

char	**ft_split_pipe(char *str, int *pipe_cnt)
{
	int		word_index;
	int		word_cnt;
	char	**new_str;

	word_index = 0;
	word_cnt = count_word(str) + 1;
	*pipe_cnt = word_cnt;
	new_str = (char **)malloc(sizeof(char *) * (word_cnt + 1));
	if (!new_str)
		return (NULL);
	new_str[word_cnt] = 0;
	while (word_cnt--)
	{
		while (*str && *str == '|')
			str++;
		new_str[word_index] = (char *)malloc(len_word(str) + 1);
		if (!new_str[word_index])
			return (free_malloc(new_str, word_index));
		new_str[word_index][len_word(str)] = 0;
		set_string(&new_str[word_index++], &str, len_word(str));
	}
	return (new_str);
}
