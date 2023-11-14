/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 09:57:45 by sgo               #+#    #+#             */
/*   Updated: 2023/11/14 18:59:42 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int		go_to_home(t_envp *envp, t_info *info);
int		go_to_oldpwd(t_envp *envp, t_info *info);
char	*get_envp_value(t_envp *envp, char *key);
int		go_to_path_home(char *path, t_envp *envp, t_info *info);

extern int	g_exit_status;

void	ft_cd(char **cmd, t_info *info, t_envp *envp)
{
	if (cmd[0] == NULL || ft_strncmp(cmd[0], "~", 2) == 0)
		g_exit_status = go_to_home(envp, info);
	else if (ft_strncmp(cmd[0], "-", 2) == 0)
		g_exit_status = go_to_oldpwd(envp, info);
	else if (ft_strncmp(cmd[0], "~/", 2) == 0)
		g_exit_status = go_to_path_home(cmd[0], envp, info);
	else 
	{
		if (chdir(cmd[0]) == -1)
		{
			g_exit_status = 1;
			ft_perror(cmd[0], info);
		}
	}
}

int	go_to_home(t_envp *envp, t_info *info)
{
	char	*home;

	home = get_envp_value(envp, "HOME");
	if (home == NULL)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		return (1);
	}
	if (chdir(home) == -1)
	{
		ft_perror(home, info);
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
		return (1);
	}
	if (chdir(oldpwd) == -1)
	{
		ft_perror(oldpwd, info);
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
		envp = envp->next;
	}
	return (NULL);
}

int	go_to_path_home(char *path, t_envp *envp, t_info *info)
{
	char	*home;
	char	*res;

	home = get_envp_value(envp, "HOME");
	if (home == NULL)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		return (1);
	}
	res = ft_strjoin(home, path + 1);
	if (chdir(res) == -1)
	{
		ft_perror(res, info);
		return (1);
	}
	return (0);
}
