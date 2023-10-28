/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:25:27 by seoson            #+#    #+#             */
/*   Updated: 2023/10/28 12:00:39 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	malloc_cmd(t_cmd *cmd, t_cmd **new_cmd)
{
	if (cmd->next == NULL)
	{
		cmd->next = (t_cmd *)malloc(sizeof(t_cmd));
		*new_cmd = cmd->next;
	}
	else
	{
		*new_cmd = cmd->next;
		while ((*new_cmd)->next != NULL)
			*new_cmd = (*new_cmd)->next;
		(*new_cmd)->next = (t_cmd *)malloc(sizeof(t_cmd));
		*new_cmd = (*new_cmd)->next;
	}
}

void	tokenize(char *str, t_cmd *cmd)
{
	t_cmd	*new_cmd;
	t_token	*token_header;
	int		curr_index;
	int		before_index;

	malloc_cmd(cmd, &new_cmd);
	token_header = (t_token *)malloc(sizeof(t_token));
	if (token_header == NULL)
		return ;
	curr_index = 0;
	while (str[curr_index] == ' ' || str[curr_index] == '\t')
		curr_index++;
	before_index = curr_index;
	while (str[curr_index] && str)
	{
		if (str[curr_index] == '\'' || str[curr_index] == '"')
			make_quote_token(str, token_header, &curr_index, &before_index);
		else if (str[curr_index + 1] == '\0' || str[curr_index] == ' ' || str[curr_index] == '\t')
			make_cmd_token(str, token_header, &curr_index, &before_index);
		else if (str[curr_index] == '>' || str[curr_index] == '<')
			make_redir_token(str, token_header, &curr_index, &before_index);
		curr_index++;
	}
	if (set_quote(token_header->next) == -1)
		return ;
}

void	parse(char *line, t_cmd *cmd)
{
	char	**pipe_split_line;
	int		pipe_cnt;
	int		pipe_index;

	pipe_cnt = 0;
	pipe_index = -1;
	pipe_split_line = ft_split(line, '|', &pipe_cnt);
	cmd->next = NULL;
	while (++pipe_index < pipe_cnt)
		tokenize(pipe_split_line[pipe_index], cmd);
	free(pipe_split_line);
	return ;
}
		