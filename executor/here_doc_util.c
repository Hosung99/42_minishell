/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 16:32:19 by sgo               #+#    #+#             */
/*   Updated: 2023/11/23 17:49:05 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*make_random_here_doc(int index)
{
	char	*filename;
	char	*tmpname;
	char	*tmp;

	tmpname = ft_strdup(HERE_DOC_FILE);
	tmp = ft_itoa(index);
	filename = ft_strjoin(tmpname, tmp);
	ft_free(tmp);
	ft_free(tmpname);
	return (filename);
}

int	check_heredoc(t_cmd *cmd)
{
	t_cmd	*temp_cmd;
	t_redir	*temp_redir;

	temp_cmd = cmd;
	while (temp_cmd)
	{
		temp_redir = temp_cmd->redir;
		while (temp_redir)
		{
			if (ft_strncmp(temp_redir->str, "<<", 3) == 0)
				return (1);
			temp_redir = temp_redir->next;
		}
		temp_cmd = temp_cmd->next;
	}
	return (0);
}

int	have_here_doc(t_cmd *cmd)
{
	t_redir	*temp_redir;

	if (cmd == NULL || cmd->redir == NULL)
		return (0);
	temp_redir = cmd->redir;
	while (temp_redir)
	{
		if (ft_strncmp(temp_redir->str, "<<", 3) == 0)
			return (1);
		temp_redir = temp_redir->next;
	}
	return (0);
}
