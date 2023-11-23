/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 16:32:19 by sgo               #+#    #+#             */
/*   Updated: 2023/11/23 14:46:20 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	*make_random_here_doc(int index)
{
	char	*filename;
	char	*tmp;

	filename = ft_strdup(HERE_DOC_FILE);
	tmp = ft_itoa(index);
	filename = ft_strjoin(filename, tmp);
	ft_free(tmp);
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

char	*get_readline(void)
{
	char	*tmp;

	tmp = readline("> ");
	if (!tmp)
	{
		printf(">");
		exit(1);
	}
	return (tmp);
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
