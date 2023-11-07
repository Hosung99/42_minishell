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
	printf("export\n");
	tmpenv = envp;
	keyval = ft_split(cmd[0], '=', &cnt);
	while (tmpenv)
	{
		if (ft_strncmp(tmpenv->key, keyval[0], ft_strlen(tmpenv->key)) == 0)
		{
			tmpenv->value = keyval[1]; // value 없을떄 예외처리 해야함.
			return ;
		}
		tmpenv = tmpenv->next;
	}
	tmpenv = (t_envp *)malloc(sizeof(t_envp));
	tmpenv->key = keyval[0];
	tmpenv->value = keyval[1];
	free(keyval);
}
