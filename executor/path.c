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
	t_envp	*tmp;
	int		cnt;

	if (envp == NULL)
		return (0); // error 처리 예정
	tmp = envp;
	while (tmp)
	{
		if (ft_strncmp(key, tmp->key, 4) == 0)
		{
			res = ft_split(tmp->value, ':', &cnt);
			return (res);
		}
		tmp = tmp->next;
	}
	return (0);
}
