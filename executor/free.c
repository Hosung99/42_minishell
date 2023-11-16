/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 01:11:15 by sgo               #+#    #+#             */
/*   Updated: 2023/11/14 19:01:47 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	free_info(t_info *info)
{
	free_str(info->cmd_path);
	if (info->cmd)
		free(info->cmd);
	close(info->pipe_fd[0]);
	close(info->pipe_fd[1]);
	free_cmd(&info->cmd_start);
	// free_envp(info->envp_start);
}

void	free_envp(t_envp *envp)
{
	t_envp	*envp_temp;

	if (envp == NULL)
		return ;
	while (envp)
	{
		envp_temp = envp;
		if (envp->key)
			free(envp->key);
		if (envp->value)
			free(envp->value);
		envp = envp->next;
		free(envp_temp);
	}	
}

void	exit_free(t_info *info)
{
	free_info(info);
	exit(g_exit_status);
}
