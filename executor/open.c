/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 01:01:34 by sgo               #+#    #+#             */
/*   Updated: 2023/11/18 18:45:32 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	open_infile(t_redir *redir, t_info *info);
void	open_outfile(t_redir *redir, t_info *info);
void	open_appendfile(t_redir *redir, t_info *info);

void	file_open(t_cmd *cmd, t_info *info)
{
	t_redir	*temp;

	if (cmd->redir == NULL)
		return ;
	temp = cmd->redir;
	while (temp)
	{
		if (ft_strncmp(temp->str, "<", 2) == 0)
			open_infile(temp, info);
		else if (ft_strncmp(temp->str, ">", 2) == 0)
			open_outfile(temp, info);
		else if (ft_strncmp(temp->str, ">>", 3) == 0)
			open_appendfile(temp, info);
		else if (ft_strncmp(temp->str, "<<", 3) == 0)
		{
			close(info->tmp_fd);
			info->tmp_fd = dup(cmd->here_doc_fd);
		}
		temp = temp->next;
	}
}

void	open_infile(t_redir *redir, t_info *info)
{
	close(info->tmp_fd);
	info->tmp_fd = open(redir->filename, O_RDONLY);
	if (info->tmp_fd < 0)
		ft_perror(redir->filename);
}

void	open_outfile(t_redir *redir, t_info *info)
{
	close(info->outfile_fd);
	info->outfile_fd = open(redir->filename, \
		O_WRONLY | O_CREAT | O_TRUNC, 0644);
	info->have_outfile = 1;
}

void	open_appendfile(t_redir *redir, t_info *info)
{
	close(info->outfile_fd);
	info->outfile_fd = open(redir->filename, \
		O_WRONLY | O_CREAT | O_APPEND, 0644);
	info->have_outfile = 1;
}
