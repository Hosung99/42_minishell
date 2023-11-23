/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:38:45 by seoson            #+#    #+#             */
/*   Updated: 2023/11/23 16:10:01 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_status;

int	is_redir(char str)
{
	if (str == '<' || str == '>')
		return (SUCCESS);
	return (0);
}

int	check_first_char(char *line)
{
	int	line_index;

	line_index = 0;
	while (line[line_index] == ' ' || line[line_index] == '\t')
		line_index++;
	if (line[line_index] == '|')
	{
		printf("minishell: syntax error near unexpected token '|'\n");
		g_exit_status = 258;
		return (0);
	}
	return (1);
}

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
	while (str[str_index])
	{
		if (str[str_index] == '<' || str[str_index] == '>')
		{
			if (str_index != 0 && (is_redir(str[str_index - 1]) \
				&& str[str_index] != str[str_index - 1]))
				count = 2;
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
