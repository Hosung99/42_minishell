/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_envp_key.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:05:09 by seoson            #+#    #+#             */
/*   Updated: 2023/11/21 20:46:33 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_status;

static int	ft_strcmp(char *key, char *str)
{
	int	index;

	index = 0;
	while (key && str && key[index] && str[index])
	{
		if (key[index] != str[index])
			return (FAILURE);
		index++;
	}
	if (key && str && key[index] == '\0' && str[index] == '\0')
		return (SUCCESS);
	return (FAILURE);
}

char	*ft_search_envp_key(t_envp *envp_list, char *str)
{
	t_envp	*envp_temp;

	if (str == NULL)
		return (NULL);
	envp_temp = envp_list->next;
	while (envp_temp)
	{
		if ((ft_strcmp("?", str)) == SUCCESS)
		{
			free(str);
			return (ft_itoa(g_exit_status));
		}
		if (ft_strcmp(envp_temp->key, str) == SUCCESS)
		{
			free(str);
			return (ft_strdup(envp_temp->value));
		}
		envp_temp = envp_temp->next;
	}
	free(str);
	return (ft_strdup(""));
}
