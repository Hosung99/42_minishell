/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:39:19 by seoson            #+#    #+#             */
/*   Updated: 2023/11/23 18:01:46 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*get_last_cmd(t_cmd *cmd)
{
	if (cmd == NULL)
		return (NULL);
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}

void	set_redir(t_token *token_header, t_cmd **cmd)
{
	t_redir	*redir_temp;
	t_redir	*new_redir;
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

int	check_token_type(t_token *token, int token_before_type)
{
	if ((token_before_type == TOKEN_READ_REDIR \
	|| token_before_type == TOKEN_WRITE_REDIR) && (token->type \
		== TOKEN_READ_REDIR || token->type == TOKEN_WRITE_REDIR)
		&& (token_before_type != token->type))
		return (FAILURE);
	return (SUCCESS);
}

int	process_token(t_token **token, t_cmd **cmd, int *option_cnt)
{
	if ((*token)->type == TOKEN_WORD || (*token)->type == TOKEN_D_QUOTE || \
		(*token)->type == TOKEN_S_QUOTE)
		make_cmd(*token, cmd, option_cnt);
	else if ((*token)->type == TOKEN_READ_REDIR \
		|| (*token)->type == TOKEN_WRITE_REDIR)
	{
		if ((*token)->next == NULL)
			return (FAILURE);
		set_redir(*token, cmd);
		if ((*token)->next != NULL \
			&& ((*token)->next->type == TOKEN_WORD || (*token)->next->type))
				*token = (*token)->next;
	}
	return (SUCCESS);
}

int	set_cmd(t_token *token_header, t_cmd **cmd)
{
	int	token_before_type;
	int	option_cnt;

	option_cnt = 0;
	token_before_type = -1;
	malloc_cmd(token_header, cmd);
	while (token_header)
	{
		if (check_token_type(token_header, token_before_type) == FAILURE)
			return (FAILURE);
		if (process_token(&token_header, cmd, &option_cnt) == FAILURE)
			return (FAILURE);
		token_before_type = token_header->type;
		token_header = token_header->next;
	}
	return (SUCCESS);
}
