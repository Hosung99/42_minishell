/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 09:21:50 by sgo               #+#    #+#             */
/*   Updated: 2023/10/31 01:22:50 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	**find_path(t_envp *envp)
{
	char	**res;
	int		cnt;

	while (envp)
	{
		if (ft_strncmp("PATH=", envp->key, 5) == 0)
		{
			res = ft_split(envp->value, ':', &cnt);
			return (res);
		}
	}
	return (0);
}
