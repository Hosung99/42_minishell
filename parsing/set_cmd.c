/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:39:19 by seoson            #+#    #+#             */
/*   Updated: 2023/11/01 21:14:11 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_token_option(t_token *token_header)
{
	int		option_cnt;
	t_token *token_temp;

	option_cnt = 0;
	token_temp = token_header;
	while (token_temp)
	{
		if (token_temp->type == token_option)
			option_cnt++;
		else
			break ;
		token_temp = token_temp->next;
	}
	return (option_cnt);
}

void	malloc_cmd(t_token *token_header, t_cmd **cmd)
{
	*cmd = (t_cmd *)malloc(sizeof(t_cmd));
	(*cmd)->cmd = (char **)malloc(sizeof(char *) * count_token_option(token_header) + 1);
	(*cmd)->cmd[count_token_option(token_header) + 1] = NULL;
	(*cmd)->redir = NULL;
	(*cmd)->next = NULL;
}

void	make_cmd(t_token *token_header, t_cmd **cmd, int *option_cnt)
{
	t_cmd	*cmd_temp;
	t_cmd	*new_cmd;

	cmd_temp = *cmd;
	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	new_cmd->cmd = (char **)malloc(sizeof(char *) \
		* count_token_option(token_header) + 1);
	new_cmd->cmd[count_token_option(token_header) + 1] = NULL;
	new_cmd->cmd[0] = ft_strdup(token_header->str);
	new_cmd->redir = NULL;
	if (*cmd == NULL)
	{
		*cmd = new_cmd;
		(*cmd)->next = NULL;
	}
	else
	{
		while (cmd_temp->next != NULL)
			cmd_temp = cmd_temp->next;
		cmd_temp->next = new_cmd;
		cmd_temp->next->next = NULL;
	}
	*option_cnt = 0;
}

void	set_option(t_token *token_header, t_cmd **cmd, int *option_cnt)
{
	*option_cnt = *option_cnt + 1;
	if (*cmd == NULL)
	{
		malloc_cmd(token_header, cmd);
		(*cmd)->cmd[0] = ft_strdup(token_header->str);
	}
	else
	{
		(*cmd)->cmd = (char **)realloc((*cmd)->cmd, sizeof(char *) * (*option_cnt + 1));
        (*cmd)->cmd[*option_cnt] = ft_strdup(token_header->str);
	}
}

void	set_redir(t_token *token_header, t_cmd **cmd)
{
	t_redir	*redir_temp;
	t_redir	*new_redir;

	redir_temp = (*cmd)->redir;
	new_redir = (t_redir *)malloc(sizeof(t_redir));
	new_redir->str = ft_strdup(token_header->str);
	if (token_header->next != NULL)
		new_redir->filename = ft_strdup(token_header->next->str);
	if (*cmd == NULL)
		malloc_cmd(token_header, cmd);
	if ((*cmd)->redir == NULL)
	{
		(*cmd)->redir = new_redir;
		(*cmd)->redir->next = NULL;
	}
	else
	{
		while (redir_temp->next != NULL)
			redir_temp = redir_temp->next;
		redir_temp->next = new_redir;
		redir_temp->next->next = NULL;
	}	
}

void	set_cmd(t_token *token_header, t_cmd **cmd)
{
	int	option_cnt;

	option_cnt = 0;
	while (token_header)
	{
		if (token_header->type == token_cmd)
			make_cmd(token_header, cmd, &option_cnt);
		else if (token_header->type == token_option)
			set_option(token_header, cmd, &option_cnt);
		else if (token_header->type == token_read_redir || \
			token_header->type == token_write_redir)
		{
			set_redir(token_header, cmd);
			if (token_header->next != NULL)
				token_header = token_header->next;
		}
		token_header = token_header->next;
	}
}
