/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 01:01:34 by sgo               #+#    #+#             */
/*   Updated: 2023/10/31 01:04:39 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	file_open(t_cmd *cmd, t_info *info)
{
	if (cmd->redir->filename == NULL)
		return ;
	info->tmp_fd = open(cmd->redir->filename, O_RDONLY);
	if (info->tmp_fd < 0)
		perror(cmd->redir->filename);
}
