/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 01:01:34 by sgo               #+#    #+#             */
/*   Updated: 2023/11/23 16:09:16 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	open_infile(t_redir *redir, t_info *info, int *res);
void	open_outfile(t_redir *redir, t_info *info, int *res);
void	open_appendfile(t_redir *redir, t_info *info, int *res);

int	file_open(t_cmd *cmd, t_info *info)
{
	t_redir	*temp;
	int		res;

	res = SUCCESS;
	if (cmd->redir == NULL)
		return (res);
	temp = cmd->redir;
	while (temp)
	{
		if (ft_strncmp(temp->str, "<", 2) == 0)
			open_infile(temp, info, &res);
		else if (ft_strncmp(temp->str, ">", 2) == 0)
			open_outfile(temp, info, &res);
		else if (ft_strncmp(temp->str, ">>", 3) == 0)
			open_appendfile(temp, info, &res);
		else if (ft_strncmp(temp->str, "<<", 3) == 0)
		{
			close(info->tmp_fd);
			info->tmp_fd = dup(cmd->here_doc_fd);
		}
		if (res == FAILURE)
			return (res);
		temp = temp->next;
	}
	return (res);
}

void	open_infile(t_redir *redir, t_info *info, int *res)
{
	close(info->tmp_fd);
	info->tmp_fd = open(redir->filename, O_RDONLY);
	if (info->tmp_fd < 0)
	{
		ft_perror(redir->filename);
		*res = FAILURE;
	}
}

void	open_outfile(t_redir *redir, t_info *info, int *res)
{
	close(info->outfile_fd);
	info->outfile_fd = open(redir->filename, \
		O_WRONLY | O_CREAT | O_TRUNC, 0644);
	info->have_outfile = 1;
	if (info->outfile_fd < 0)
	{
		ft_perror(redir->filename);
		*res = FAILURE;
	}
}

void	open_appendfile(t_redir *redir, t_info *info, int *res)
{
	close(info->outfile_fd);
	info->outfile_fd = open(redir->filename, \
		O_WRONLY | O_CREAT | O_APPEND, 0644);
	info->have_outfile = 1;
	if (info->outfile_fd < 0)
	{
		ft_perror(redir->filename);
		*res = FAILURE;
	}
}
