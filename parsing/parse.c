/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:25:27 by seoson            #+#    #+#             */
/*   Updated: 2023/11/12 18:16:01 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
extern int g_exit_status;

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

void	free_token(t_token *token_header)
{
    t_token *token_header_temp;

	while (token_header != NULL)
    {
		token_header_temp = token_header;
		token_header = token_header->next;
		free(token_header_temp->str);
        free(token_header_temp);
    }
	free(token_header);
}

int isMetachar(char curr)
{
	if (curr == '<' || curr == '>' || curr == ' ' || curr == '\t' || \
		curr == '"' || curr == '\'')
		return (1);
	else
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
		if (isMetachar(str[*curr_index]) == 1)
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
	while (str[curr_index] && str)
	{
		if (isMetachar(str[curr_index]) == 1)
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

int	parse(char *line, t_cmd **cmd, t_envp *envp_list)
{
	char	**pipe_split_line;
	int		pipe_cnt;
	int		pipe_index;

	pipe_cnt = 0;
	pipe_index = -1;
	pipe_split_line = ft_split(line, '|', &pipe_cnt); //따옴표 안에 파이프는 문자열 밀기.
	*cmd = NULL;
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
