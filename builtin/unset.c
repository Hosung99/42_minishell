/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:04:10 by sgo               #+#    #+#             */
/*   Updated: 2023/10/31 01:20:25 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_unset(char **cmd, t_info *info, t_envp *envp)
{
	t_envp	*tmpenv;

	(void)info;
	tmpenv = envp;
	while (tmpenv)
	{
		if (ft_strncmp(tmpenv->key, cmd[0], ft_strlen(tmpenv->key)) == 0)
		{
			tmpenv->key = NULL;
			tmpenv->value = NULL;
			return ;
		}
		tmpenv = tmpenv->next;
	}
}
