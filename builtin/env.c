/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:42:00 by sgo               #+#    #+#             */
/*   Updated: 2023/10/29 17:04:24 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	ft_env(t_envp *envp)
{
	//env 없을때 처리 할 예정
	
	while (envp)
	{
		ft_putstr_fd(envp->key, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(envp->value, 1);
		ft_putchar_fd('\n', 1);
		envp = envp->next;
	}
}