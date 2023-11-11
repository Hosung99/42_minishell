/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:15:14 by sgo               #+#    #+#             */
/*   Updated: 2023/11/11 12:15:37 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	envp_cnt(t_envp *envp);

char	**get_envp(t_envp *envp)
{
	char	**input_envp;
	char	*key;
	int		i;

	i = 0;
	input_envp = (char **)malloc(sizeof(char *) * (envp_cnt(envp) + 1));
	if (input_envp == NULL)
		return (NULL);
	while (envp)
	{
		if (envp->key != NULL)
		{
			key = ft_strjoin(envp->key, "=");
			if (key == NULL)
				return (NULL);
			if (envp->value == NULL)
				input_envp[i] = ft_strdup(key);
			else
				input_envp[i] = ft_strjoin(key, envp->value);
			free(key);
			if (input_envp[i] == NULL)
				return (NULL);
			i++;
		}
		envp = envp->next;
	}
	input_envp[i] = NULL;
	return (input_envp);
}

int	envp_cnt(t_envp *envp)
{
	int	cnt;

	cnt = 0;
	while (envp)
	{
		if (envp->key != NULL)
			cnt++;
		envp = envp->next;
	}
	return (cnt);
}
