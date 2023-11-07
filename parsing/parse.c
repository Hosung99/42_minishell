/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:25:27 by seoson            #+#    #+#             */
/*   Updated: 2023/11/07 22:39:54 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_token(t_token *token_header)
{
	t_token	*token_first;
    t_token *token_header_temp;

	token_first = token_header;
	token_header = token_header->next;
    while (token_header)
    {
        token_header_temp = token_header;
       	free(token_header_temp->str);
        free(token_header_temp);
		token_header = token_header->next;
    }
	free(token_first);
}

int	tokenize(char *str, t_cmd **cmd, t_envp *envp_list)
{
	t_token	*token_header;
	int		curr_index;
	int		before_index;

	token_header = ft_calloc(1, sizeof(t_token));
	(void)token_header;
	curr_index = 0;
	while (str[curr_index] == ' ' || str[curr_index] == '\t')
		curr_index++;
	before_index = curr_index;
	while (str[curr_index] && str)
	{
		if (str[curr_index] == '\'' || str[curr_index] == '"')
			make_quote_token(str, token_header, &curr_index, &before_index);
		else if (str[curr_index + 1] == '\0' || \
			str[curr_index] == ' ' || str[curr_index] == '\t')
			make_cmd_token(str, token_header, &curr_index, &before_index);
		else if (str[curr_index] == '>' || str[curr_index] == '<')
			make_redir_token(str, token_header, &curr_index, &before_index);
		if (str[curr_index] != '\0')
			curr_index++;
	}
	(void)envp_list;
	(void)cmd;
	// if (set_quote(token_header->next, envp_list, cmd) == -1)
	// {
	// 	free_token(token_header);
	// 	return (-1);
	// }
	free_token(token_header);
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

int	parse(char *line, t_cmd **cmd, t_envp *envp_list)
{
	char	**pipe_split_line;
	int		pipe_cnt;
	int		pipe_index;

	pipe_cnt = 0;
	pipe_index = -1;
	pipe_split_line = ft_split(line, '|', &pipe_cnt);
	*cmd = NULL;
	while (++pipe_index < pipe_cnt)
	{
		if (before_check_quote(pipe_split_line[pipe_index]))
		{
			free_str(pipe_split_line);
			printf("minishell: syntax error near unexpected quote\n");
			return (-1);
		}
		if (tokenize(pipe_split_line[pipe_index], cmd, envp_list) == -1)
		{
			free_str(pipe_split_line);
			return (-1);
		}
	}
	free_str(pipe_split_line);
	return (1);
}
