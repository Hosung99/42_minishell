/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 09:52:04 by sgo               #+#    #+#             */
/*   Updated: 2023/11/17 19:47:41 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "../executor/executor.h"

void	ft_cd(char **cmd, t_envp *envp);
void	echo(char **args);
void	ft_env(t_envp *envp);
void	ft_exit(char **cmd, t_info *info);
void	ft_pwd(void);
void	ft_export(char **cmd, t_envp *envp);
void	ft_unset(char **cmd, t_envp *envp);
void	export_oldpwd(char *oldpwd, t_envp *envp);

#endif