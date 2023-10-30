/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 09:52:04 by sgo               #+#    #+#             */
/*   Updated: 2023/10/31 01:20:18 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

#include "../executor/executor.h"

void	ft_cd(char **cmd, t_info *info, t_envp *envp);
void	echo(char **args);
void	ft_env(t_envp *envp);
void	ft_exit(t_cmd *cmd, t_info *info, t_envp *envp);
void	ft_pwd();
void	ft_export(char **cmd, t_info *info, t_envp *envp);
void	ft_unset(char **cmd, t_info *info, t_envp *envp);

#endif