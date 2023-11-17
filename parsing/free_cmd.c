/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:51:47 by seoson            #+#    #+#             */
/*   Updated: 2023/11/17 12:26:51 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_str(char **str)
{
	int	str_index;

	str_index = 0;
	if (str == NULL)
		return ;
	while (str[str_index])
	{
		free(str[str_index]);
		str_index++;
	}
	free(str);
}

void	free_redir(t_redir *redir)
{
	t_redir	*redir_temp;

	while (redir)
	{
		redir_temp = redir->next;
		free(redir->str);
		free(redir->filename);
		free(redir);
		redir = redir_temp;
	}
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*cmd_temp;

	while (*cmd)
	{
		cmd_temp = (*cmd)->next;
		free_str((*cmd)->cmd);
		free_redir((*cmd)->redir);
		free(*cmd);
		*cmd = cmd_temp;
	}
	free(*cmd);
}

void	free_token(t_token *token_header)
{
	t_token	*token_header_temp;

	while (token_header != NULL)
	{
		token_header_temp = token_header;
		token_header = token_header->next;
		free(token_header_temp->str);
		free(token_header_temp);
	}
}
