/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:42:00 by sgo               #+#    #+#             */
/*   Updated: 2023/11/23 17:16:27 by sgo              ###   ########.fr       */
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
	char	*oldpwd_value;
	t_envp	*tmpenv;

	oldpwd_value = ft_strdup(oldpwd);
	tmpenv = envp;
	while (tmpenv)
	{
		if (tmpenv->key && \
			ft_strncmp(tmpenv->key, OLD_PWD, ft_strlen(OLD_PWD) + 1) == 0)
		{
			ft_free(tmpenv->value);
			tmpenv->value = oldpwd_value;
			tmpenv->have_equal = 1;
			return ;
		}
		if (tmpenv->next == NULL)
		{
			tmpenv->next = new_envp(OLD_PWD, oldpwd_value, 1);
			return ;
		}
		tmpenv = tmpenv->next;
	}
	ft_free(oldpwd_value);
}
