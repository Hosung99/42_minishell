/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:39:19 by seoson            #+#    #+#             */
/*   Updated: 2023/11/12 18:04:31 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_token_option(t_token *token_header)
{
	int		word_cnt;
	int		redir_cnt;
	t_token	*token_temp;

	word_cnt = 0;
	redir_cnt = 0;
	token_temp = token_header;
	while (token_temp)
	{
		if (token_temp->type == TOKEN_READ_REDIR || token_temp->type == TOKEN_WRITE_REDIR)
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
			cmd_temp->next->cmd = (char **)ft_calloc(cnt_token + 2, sizeof(char *));
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

t_cmd *get_last_cmd(t_cmd *cmd)
{
	if (cmd == NULL)
		return NULL;
	while (cmd->next != NULL)
		cmd = cmd->next;
	return cmd;
}

void set_redir(t_token *token_header, t_cmd **cmd)
{
	t_redir *redir_temp;
	t_redir *new_redir;
	t_cmd	*last_cmd;

	new_redir = (t_redir *)ft_calloc(1, sizeof(t_redir));
	new_redir->str = ft_strdup(token_header->str);
	new_redir->next = NULL;
	if (token_header->next != NULL)
		new_redir->filename = ft_strdup(token_header->next->str);
	last_cmd = get_last_cmd(*cmd);
	if (last_cmd->redir == NULL)
		last_cmd->redir = new_redir;
	else
	{
		redir_temp = last_cmd->redir;
		while (redir_temp->next != NULL)
			redir_temp = redir_temp->next;
		redir_temp->next = new_redir;
	}
}

int	set_cmd(t_token *token_header, t_cmd **cmd)
{
	int	option_cnt;
	int	token_before_type;

	option_cnt = 0;
	token_before_type = -1;
	malloc_cmd(token_header, cmd);
	while (token_header)
	{
		printf("AFTER PARSING : %s\n", token_header->str);
		if ((token_before_type == TOKEN_READ_REDIR || token_before_type == TOKEN_WRITE_REDIR) &&
			(token_header->type == TOKEN_READ_REDIR || token_header->type == TOKEN_WRITE_REDIR))
			return (-1);
		if (token_header->type == TOKEN_WORD)
			make_cmd(token_header, cmd, &option_cnt);
		else if (token_header->type == TOKEN_READ_REDIR || \
			token_header->type == TOKEN_WRITE_REDIR)
		{
			if (token_header->next == NULL)
				return (-1);
			set_redir(token_header, cmd);
			if (token_header->next != NULL && token_header->next->type == TOKEN_WORD)
				token_header = token_header->next;
		}
		token_before_type = token_header->type;
		token_header = token_header->next;
	}
	return (1);
}
