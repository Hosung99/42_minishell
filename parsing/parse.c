/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:25:27 by seoson            #+#    #+#             */
/*   Updated: 2023/11/14 16:01:40 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_status;

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

void	set_token(t_token *token_header, char *str, int *curr_index)
{
	if (str[*curr_index] == '\'' || str[*curr_index] == '"')
		*curr_index = make_quote_token(str, token_header, *curr_index);
	else if (str[*curr_index] == ' ' || str[*curr_index] == '\t')
		*curr_index = make_cmd_token(str, token_header, *curr_index);
	else if (str[*curr_index] == '>' || str[*curr_index] == '<')
		*curr_index = make_redir_token(str, token_header, *curr_index);
}

void	set_normal_token(t_token *token_header, char *str, int *curr_index)
{
	t_token	*new_token;

	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	while (str[*curr_index])
	{
		if (is_metachar(str[*curr_index]) == 1)
			break ;
		new_token->str = ft_strjoin_char(new_token->str, str[*curr_index]);
		*curr_index = *curr_index + 1;
	}
	new_token->type = TOKEN_WORD;
	new_token->next = NULL;
	set_token_position(token_header, new_token);
}

int	tokenize(char *str, t_cmd **cmd, t_envp *envp_list)
{
	t_token	*token_header;
	int		curr_index;

	token_header = (t_token *)ft_calloc(1, sizeof(t_token));
	curr_index = 0;
	while (str[curr_index] == ' ' || str[curr_index] == '\t')
		curr_index++;
	(void)cmd;
	(void)envp_list;
	while (str[curr_index] && str)
	{
		if (is_metachar(str[curr_index]) == 1)
			set_token(token_header, str, &curr_index);
		else
			set_normal_token(token_header, str, &curr_index);
	}
	if (set_quote(token_header->next, envp_list, cmd) == -1)
	{
		free_token(token_header);
		return (-1);
	}
	free_token(token_header);
	return (1);
}

int	before_check_pipe(char *line)
{
	char	before_char;
	int		str_index;

	str_index = 1;
	while (line[str_index])
	{
		while (line[str_index] == 32 || line[str_index] == 9)
			str_index++;
		before_char = line[str_index - 1];
		if (before_char == '|' && line[str_index] == '|')
			return (-1);
		str_index++;
	}
	if (line[str_index - 1] == '|')
		return (-1);
	return (1);
}

int	parse(char *line, t_cmd **cmd, t_envp *envp_list)
{
	char	**pipe_split_line;
	int		pipe_cnt;
	int		pipe_index;

	pipe_cnt = 0;
	pipe_index = -1;
	*cmd = NULL;
	if (before_check_pipe(line) == -1)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		g_exit_status = 1;
		return (-1);
	}
	pipe_split_line = ft_split(line, '|', &pipe_cnt); //따옴표 안에 파이프는 문자열 밀기.
	while (++pipe_index < pipe_cnt)
	{
		if (before_check_quote(pipe_split_line[pipe_index]))
		{
			free_str(pipe_split_line);
			printf("minishell: syntax error near unexpected quote\n");
			g_exit_status = 1;
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
