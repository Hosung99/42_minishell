/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:20:28 by seoson            #+#    #+#             */
/*   Updated: 2023/11/07 16:41:26 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	make_envp_cmd(t_envp *envp_list, char **str, int cnt)
{
	t_envp *envp;

	envp = (t_envp *)malloc(sizeof(t_envp));
	envp->key = ft_strdup(str[0]);
	if (cnt == 2)
		envp->value = ft_strdup(str[1]);
	envp->next = NULL;
	if (envp_list->next == NULL)
		envp_list->next = envp;
	else
	{
		envp_list = envp_list->next;
		while (envp_list->next != NULL)
			envp_list = envp_list->next;
		envp_list->next = envp;
	}
}

void	set_envp(char **envp, t_envp *envp_list)
{
	int		envp_index;
	int		split_cnt;
	char	**split_str;

	envp_index = 0;
	envp_list->next = NULL;
	while (envp[envp_index])
	{
		split_cnt = 0;
		split_str = ft_split(envp[envp_index], '=', &split_cnt);
		make_envp_cmd(envp_list, split_str, split_cnt);
		free_str(split_str);
		envp_index++;
	}
}
