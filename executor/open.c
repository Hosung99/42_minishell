/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 01:01:34 by sgo               #+#    #+#             */
/*   Updated: 2023/11/08 19:32:21 by sgo              ###   ########.fr       */
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
			here_doc(temp, info);
		temp = temp->next;
	}
}

void	open_infile(t_redir *redir, t_info *info)
{
	printf("open_infile\n");
	info->tmp_fd = open(redir->filename, O_RDONLY);
	if (info->tmp_fd < 0)
		perror(redir->filename);
}

void	open_outfile(t_redir *redir, t_info *info)
{
	printf("open_outfile\n");
	printf("filename : %s\n", redir->filename);
	info->outfile_fd = open(redir->filename, \
		O_WRONLY | O_CREAT | O_TRUNC, 0644); 
	info->have_outfile = 1;
	if (info->outfile_fd < 0)
		perror(redir->filename);
}

void	open_appendfile(t_redir *redir, t_info *info)
{
	printf("open_appendfile\n");
	info->outfile_fd = open(redir->filename, \
		O_WRONLY | O_CREAT | O_APPEND, 0644); 
	if (info->outfile_fd < 0)
		perror(redir->filename);
}
