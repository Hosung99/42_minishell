/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:42:00 by sgo               #+#    #+#             */
/*   Updated: 2023/11/21 06:52:07 by sgo              ###   ########.fr       */
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
			ft_putstr_fd(envp->key, STDOUT_FILENO);
			ft_putchar_fd('=', STDOUT_FILENO);
			if (envp->value != NULL)
				ft_putstr_fd(envp->value, STDOUT_FILENO);
			ft_putchar_fd('\n', STDOUT_FILENO);
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
