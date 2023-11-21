/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:54:46 by seoson            #+#    #+#             */
/*   Updated: 2023/11/21 20:42:46 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_token_option(t_token *token_header)
{
	int		word_cnt;
	int		redir_cnt;
	t_token	*token_temp;

	word_cnt = 0;
	redir_cnt = 0;
	token_temp = token_header;
	while (token_temp)
	{
		if (token_temp->type == TOKEN_READ_REDIR \
			|| token_temp->type == TOKEN_WRITE_REDIR)
			redir_cnt++;
		token_temp = token_temp->next;
	}
	token_temp = token_header;
	while (token_temp)
	{
		if (token_temp->type == TOKEN_WORD)
			word_cnt++;
		token_temp = token_temp->next;
	}
	if (word_cnt - redir_cnt < 0)
		return (0);
	return (word_cnt - redir_cnt);
}

void	malloc_cmd(t_token *token_header, t_cmd **cmd)
{
	int		cnt_token;
	t_cmd	*cmd_temp;

	cnt_token = count_token_option(token_header);
	if (*cmd == NULL)
	{
		*cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
		(*cmd)->cmd = (char **)ft_calloc(cnt_token + 2, sizeof(char *));
		(*cmd)->redir = NULL;
		(*cmd)->next = NULL;
	}
	else
	{
		cmd_temp = *cmd;
		while (cmd_temp->next != NULL)
			cmd_temp = cmd_temp->next;
		cmd_temp->next = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
		if (cnt_token > 0)
			cmd_temp->next->cmd = (char **)ft_calloc(cnt_token + 2, \
				sizeof(char *));
		cmd_temp->next->redir = NULL;
		cmd_temp->next->next = NULL;
	}
}

void	make_cmd(t_token *token_header, t_cmd **cmd, int *option_cnt)
{
	t_cmd	*cmd_temp;

	cmd_temp = *cmd;
	while (cmd_temp->next != NULL)
		cmd_temp = cmd_temp->next;
	cmd_temp->cmd[*option_cnt] = ft_strdup(token_header->str);
	cmd_temp->cmd[*option_cnt + 1] = NULL;
	*option_cnt = *option_cnt + 1;
}
