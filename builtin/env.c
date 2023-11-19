/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:42:00 by sgo               #+#    #+#             */
/*   Updated: 2023/11/17 17:47:03 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_env(t_envp *envp)
{
	if (!envp)
		ft_putstr_fd("env is empty\n", 2);
	while (envp)
	{
		if (envp->key != NULL && envp->have_equal == 1)
		{
			ft_putstr_fd(envp->key, 1);
			ft_putchar_fd('=', 1);
			if (envp->value != NULL)
				ft_putstr_fd(envp->value, 1);
			ft_putchar_fd('\n', 1);
		}
		envp = envp->next;
	}
}

void	export_oldpwd(char *oldpwd, t_envp *envp)
{
	char	*oldpwd_key;
	char	*oldpwd_value;
	t_envp	*tmpenv;

	oldpwd_key = ft_strdup("OLDPWD");
	oldpwd_value = ft_strdup(oldpwd);
	tmpenv = envp;
	while (tmpenv)
	{
		if (tmpenv->key && \
			ft_strncmp(tmpenv->key, oldpwd_key, ft_strlen(oldpwd_key) + 1) == 0)
		{
			ft_free(tmpenv->value);
			tmpenv->value = oldpwd_value;
			tmpenv->have_equal = 1;
			ft_free(oldpwd_key);
			return ;
		}
		tmpenv = tmpenv->next;
	}
	ft_free(oldpwd_key);
	ft_free(oldpwd_value);
}
