/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 17:04:10 by sgo               #+#    #+#             */
/*   Updated: 2023/11/23 16:33:28 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_unset(char **cmd, t_envp *envp)
{
	t_envp	*tmpenv;
	int		index;

	index = 0;
	while (cmd[index])
	{
		tmpenv = envp;
		while (tmpenv)
		{
			if (tmpenv->key && ft_strncmp(tmpenv->key, cmd[index], \
			ft_strlen(tmpenv->key)) == 0)
			{
				ft_free(tmpenv->key);
				ft_free(tmpenv->value);
				tmpenv->key = NULL;
				tmpenv->value = NULL;
				tmpenv->have_equal = 0;
				break ;
			}
			tmpenv = tmpenv->next;
		}
		index++;
	}
	tmpenv = envp;
}
