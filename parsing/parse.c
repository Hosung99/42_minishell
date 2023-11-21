/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:25:27 by seoson            #+#    #+#             */
/*   Updated: 2023/11/21 07:05:43 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_status;

void	set_token(t_token *token_header, char *str, int *curr_index)
{
	if (str[*curr_index] == ' ' || str[*curr_index] == '\t')
		*curr_index = make_cmd_token(str, token_header, *curr_index);
	else if (str[*curr_index] == '>' || str[*curr_index] == '<')
		*curr_index = make_redir_token(str, token_header, *curr_index);
}

void	set_normal_token(t_token *token_header, char *str, int *curr_index)
{
	t_token	*new_token;
	int		quote_flag;

	quote_flag = 0;
	new_token = (t_token *)ft_calloc(1, sizeof(t_token));
	while (str[*curr_index])
	{
		if (quote_flag == 0 && (str[*curr_index] == '\'' \
			|| str[*curr_index] == '\"'))
			quote_flag = 1;
		else if (quote_flag == 1 && (str[*curr_index] == '\'' \
			|| str[*curr_index] == '\"'))
			quote_flag = 0;
		if (quote_flag == 0 && is_metachar(str[*curr_index]) == 1)
			break ;
		new_token->str = ft_strjoin_char(new_token->str, str[*curr_index]);
		*curr_index = *curr_index + 1;
	}
	new_token->type = set_token_type(new_token->str);
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

int	do_tokenize(char **pipe_split_line, \
	int pipe_index, t_cmd **cmd, t_envp *envp_list)
{
	if (before_check_quote(pipe_split_line[pipe_index]))
	{
		free_str(pipe_split_line);
		printf("minishell: syntax error near unexpected quote\n");
		g_exit_status = EXIT_FAILURE;
		return (-1);
	}
	if (tokenize(pipe_split_line[pipe_index], cmd, envp_list) == -1)
	{
		free_str(pipe_split_line);
		return (-1);
	}
	return (0);
}

int	parse(char *line, t_cmd **cmd, t_envp *envp_list)
{
	char	**pipe_split_line;
	int		pipe_cnt;
	int		pipe_index;

	pipe_cnt = 0;
	pipe_index = -1;
	*cmd = NULL;
	if (before_check_pipe(line) == -1 || before_check_redir(line) == -1)
	{
		g_exit_status = EXIT_FAILURE;
		return (-1);
	}
	pipe_split_line = ft_split_pipe(line, &pipe_cnt);
	if (pipe_split_line == NULL)
		exit(1);
	while (++pipe_index < pipe_cnt)
		if (do_tokenize(pipe_split_line, pipe_index, cmd, envp_list) == -1)
			return (-1);
	free_str(pipe_split_line);
	return (1);
}
