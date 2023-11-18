/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:49:08 by seoson            #+#    #+#             */
/*   Updated: 2023/11/18 17:49:29 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_init(char **envp, t_envp *envp_list, t_termios *term)
{
	set_envp(envp, envp_list);
	set_termios(term);
	update_shlvl(envp_list);
}
