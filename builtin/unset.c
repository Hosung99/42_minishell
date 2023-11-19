/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:04:10 by sgo               #+#    #+#             */
/*   Updated: 2023/11/18 17:37:26 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_unset(char **cmd, t_envp *envp)
{
	t_envp	*tmpenv;

	tmpenv = envp;
	while (tmpenv)
	{
		if (tmpenv->key && \
			ft_strncmp(tmpenv->key, cmd[0], ft_strlen(tmpenv->key)) == 0)
		{
			tmpenv->key = NULL;
			tmpenv->value = NULL;
			return ;
		}
		tmpenv = tmpenv->next;
	}
}
