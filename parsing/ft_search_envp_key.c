/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_envp_key.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:05:09 by seoson            #+#    #+#             */
/*   Updated: 2023/10/31 16:08:58 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_search_envp_key(t_envp *envp_list, char *str)
{
	t_envp *envp_temp;

	envp_temp = envp_list;
	while (envp_temp)
	{
		if (ft_strncmp(envp_temp->key, str, ft_strlen(envp_temp->key)) == 0)
			return (envp_temp->value);
		envp_temp = envp_temp->next;
	}
	return (NULL);
}