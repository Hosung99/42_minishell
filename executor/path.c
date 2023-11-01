/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 09:21:50 by sgo               #+#    #+#             */
/*   Updated: 2023/10/31 17:22:44 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	**find_path(t_envp *envp, char *key)
{
	char	**res;
	int		cnt;

	while (envp)
	{
		if (ft_strncmp(key, envp->key, 4) == 0)
		{
			res = ft_split(envp->value, ':', &cnt);
			return (res);
		}
	}
	return (0);
}
