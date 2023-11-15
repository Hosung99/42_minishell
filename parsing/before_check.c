/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:38:45 by seoson            #+#    #+#             */
/*   Updated: 2023/11/15 15:39:20 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	before_check_pipe(char *line)
{
	char	before_char;
	int		str_index;

	str_index = 1;
	while (line[str_index])
	{
		before_char = line[str_index - 1];
		while (line[str_index] == 32 || line[str_index] == 9)
			str_index++;
		if (before_char == '|' && line[str_index] == '|')
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			return (-1);
		}
		if (line[str_index] != '\0')
			str_index++;
	}
	if (line[str_index - 1] == '|')
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (-1);
	}
	return (1);
}

int	before_check_redir(char *str)
{
	int	str_index;
	int	count;

	str_index = 0;
	count = 0;
	if (ft_strlen(str) >= 3)
	{
		while (str[str_index])
		{
			if (str[str_index] == '<' || str[str_index] == '>')
			{
				count++;
				if (count == 3)
				{
					printf("minishell: syntax error unexpected token `redir'\n");
					return (-1);
				}
			}
			else
				count = 0;
			str_index++;
		}
	}
	return (1);
}

int	before_check_quote(char *line)
{
	int		quote_flag;
	char	quote_temp;

	quote_flag = 0;
	while (*line)
	{
		if (!quote_flag && (*line == '\'' || *line == '\"'))
		{
			quote_temp = *line;
			quote_flag = 1;
		}
		else if (quote_flag && *line == quote_temp)
			quote_flag = 0;
		line++;
	}
	if (quote_flag)
		return (1);
	return (0);
}
