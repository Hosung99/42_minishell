/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:55:02 by sgo               #+#    #+#             */
/*   Updated: 2023/10/31 01:20:22 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_export(char **cmd, t_info *info, t_envp *envp)
{
	t_envp	*tmpenv;
	char	**keyval;
	int		cnt;

	(void)info;
	tmpenv = envp;
	keyval = ft_split(cmd[0], '=', &cnt);
	if (cnt > 2)
		return ; // 에러처리
	while (tmpenv)
	{
		if (ft_strncmp(tmpenv->key, keyval[0], ft_strlen(tmpenv->key)) == 0)
		{
			if (cnt == 2)
				tmpenv->value = keyval[1];
			else
				tmpenv->value = ft_strdup("");
			return ;
		}
		tmpenv = tmpenv->next;
	}
	tmpenv = (t_envp *)malloc(sizeof(t_envp));
	tmpenv->key = keyval[0];
	tmpenv->value = keyval[1];
	free(keyval);
}
