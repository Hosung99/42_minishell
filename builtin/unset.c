/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:04:10 by sgo               #+#    #+#             */
/*   Updated: 2023/11/09 01:18:16 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_unset(char **cmd, t_envp *envp)
{
	t_envp	*tmpenv;

	tmpenv = envp;
	while (tmpenv)
	{
		if (tmpenv->key != NULL && ft_strncmp(tmpenv->key, cmd[0], ft_strlen(tmpenv->key)) == 0)
		{
			tmpenv->key = NULL;
			tmpenv->value = NULL;
			return ;
		}
		tmpenv = tmpenv->next;
	}
}
