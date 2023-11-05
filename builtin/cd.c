/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 09:57:45 by sgo               #+#    #+#             */
/*   Updated: 2023/11/01 15:43:26 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int		go_to_home(t_envp *envp, t_info *info);
int		go_to_oldpwd(t_envp *envp, t_info *info);
char	*get_envp_value(t_envp *envp, char *key);

void	ft_cd(char **cmd, t_info *info, t_envp *envp)
{
	if (cmd[0] == NULL || ft_strncmp(cmd[0], "~", 2) == 0)
	{
		info->status = go_to_home(envp, info);
		return ;
	}
	else if (ft_strncmp(cmd[0], "-", 2) == 0)
	{
		info->status = go_to_oldpwd(envp, info);
		return ;
	}
	if (chdir(cmd[0]) == -1)
	{
		info->status = 1;
		// 예외 메시지
		return ;
	}
	// home으로 가는 거 만들 예정
}

int	go_to_home(t_envp *envp, t_info *info)
{
	char	*home;

	home = get_envp_value(envp, "HOME");
	if (home == NULL)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		info->status = 1;
		return (1);
	}
	if (chdir(home) == -1)
	{
		// 예외 메시지
		return (1);
	}
	return (0);
}

int	go_to_oldpwd(t_envp *envp, t_info *info)
{
	char	*oldpwd;

	oldpwd = get_envp_value(envp, "OLDPWD");
	if (oldpwd == NULL)
	{
		write(2, "minishell: cd: OLDPWD not set\n", 30);
		info->status = 1;
		return (1);
	}
	if (chdir(oldpwd) == -1)
	{
		// 예외 메시지
		return (1);
	}
	return (0);
}

char	*get_envp_value(t_envp *envp, char *key)
{
	while (envp)
	{
		if (ft_strncmp(key, envp->key, ft_strlen(key)) == 0)
			return (envp->value);
	}
	return (NULL);
}