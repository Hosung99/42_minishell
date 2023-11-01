/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_envp_key.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:05:09 by seoson            #+#    #+#             */
/*   Updated: 2023/11/01 15:51:25 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_strcmp(char *key, char *str)
{
	int index;
	
	index = 0;
	while (key[index] && str[index])
	{
		if (key[index] != str[index])
			return (0);
		index++;
	}
	if (key[index] == '\0' && str[index] == '\0')
		return (1);
	return (0);
}

char	*ft_search_envp_key(t_envp *envp_list, char *str)
{
	t_envp *envp_temp;

	envp_temp = envp_list->next;
	while (envp_temp)
	{
		if (ft_strcmp(envp_temp->key, str))
		{
			free(str);
			return (envp_temp->value);
		}
		envp_temp = envp_temp->next;
	}
	free(str);
	return (NULL);
}