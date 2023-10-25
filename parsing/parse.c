/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:25:27 by seoson            #+#    #+#             */
/*   Updated: 2023/10/25 22:16:03 by seoson           ###   ########.fr       */
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

void	set_token(char *str, t_cmd *cmd)
{
	t_cmd	*new_cmd;
	t_token	*token_header;
	int		curr_index;
	int		before_index;

	malloc_cmd(cmd, &new_cmd);
	token_header = (t_token *)malloc(sizeof(t_token));
	curr_index = 0;
	while (str[curr_index] == ' ')
		curr_index++;
	before_index = curr_index;
	while (str && str[curr_index])
	{
		if ( str[curr_index + 1] == '\0' || str[curr_index] == ' ')
			make_cmd_token(str, token_header, &curr_index, &before_index);
		else if (str[curr_index] == '>' || str[curr_index] == '<')
			make_redir_token(str, token_header, &curr_index, &before_index);
		curr_index++;
	}
	printf("token_header->str : %s\n", token_header->next->str);
}

void	parse(char *line, t_cmd *cmd)
{
	char	**split_cmd_pipe;
	int		pipe_cnt;
	int		index;

	pipe_cnt = 0;
	index = -1;
	split_cmd_pipe = ft_split(line, '|', &pipe_cnt);
	cmd->next = NULL;
	while (++index < pipe_cnt)
		set_token(split_cmd_pipe[index], cmd);
	free(split_cmd_pipe);
	return ;
}
