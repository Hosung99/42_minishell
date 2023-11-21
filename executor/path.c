/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 09:21:50 by sgo               #+#    #+#             */
/*   Updated: 2023/11/21 16:46:33 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

char	**find_path(t_envp *envp, char *key)
{
	char	**res;
	t_envp	*tmp;
	int		cnt;

	if (envp == NULL)
		return (0);
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
