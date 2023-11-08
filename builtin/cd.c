/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 09:57:45 by sgo               #+#    #+#             */
/*   Updated: 2023/11/09 00:50:50 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int		go_to_home(t_envp *envp);
int		go_to_oldpwd(t_envp *envp);
char	*get_envp_value(t_envp *envp, char *key);
int		go_to_path_home(char *path, t_envp *envp);

void	ft_cd(char **cmd, t_info *info, t_envp *envp)
{
	if (cmd[0] == NULL || ft_strncmp(cmd[0], "~", 2) == 0)
		info->status = go_to_home(envp);
	else if (ft_strncmp(cmd[0], "-", 2) == 0)
		info->status = go_to_oldpwd(envp);
	else if (ft_strncmp(cmd[0], "~/", 2) == 0)
		info->status = go_to_path_home(cmd[0], envp);
	else 
	{
		if (chdir(cmd[0]) == -1)
		{
			info->status = 1;
			perror(cmd[0]);
		}
	}
}

int	go_to_home(t_envp *envp)
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
		perror(home);
		return (1);
	}
	return (0);
}

int	go_to_oldpwd(t_envp *envp)
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
		perror(oldpwd);
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

int	go_to_path_home(char *path, t_envp *envp)
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
		perror(res);
		return (1);
	}
	return (0);
}
