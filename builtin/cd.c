/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 09:57:45 by sgo               #+#    #+#             */
/*   Updated: 2023/11/23 17:16:55 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int		go_to_home(t_envp *envp);
int		go_to_oldpwd(t_envp *envp);
char	*get_envp_value(t_envp *envp, char *key);
int		go_to_path_home(char *path, t_envp *envp);

void	ft_cd(char **cmd, t_envp *envp)
{
	char	*nowpwd;

	nowpwd = getcwd(NULL, 0);
	if (cmd[0] == NULL || ft_strncmp(cmd[0], "~", 2) == 0)
		g_exit_status = go_to_home(envp);
	else if (ft_strncmp(cmd[0], "-", 2) == 0)
		g_exit_status = go_to_oldpwd(envp);
	else if (ft_strncmp(cmd[0], "~/", 2) == 0)
		g_exit_status = go_to_path_home(cmd[0], envp);
	else
	{
		if (chdir(cmd[0]) == -1)
		{
			g_exit_status = EXIT_FAILURE;
			ft_perror(cmd[0]);
		}
	}
	if (nowpwd == NULL)
	{	
		ft_perror("getcwd");
		return ;
	}
	export_oldpwd(nowpwd, envp);
	ft_free(nowpwd);
}

int	go_to_home(t_envp *envp)
{
	char	*home;

	home = get_envp_value(envp, HOME);
	if (home == NULL)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		return (1);
	}
	if (chdir(home) == -1)
	{
		ft_perror(home);
		return (1);
	}
	return (0);
}

int	go_to_oldpwd(t_envp *envp)
{
	char	*oldpwd;

	oldpwd = get_envp_value(envp, OLD_PWD);
	if (oldpwd == NULL)
	{
		write(2, "minishell: cd: OLDPWD not set\n", 30);
		return (1);
	}
	if (chdir(oldpwd) == -1)
	{
		ft_perror(oldpwd);
		return (1);
	}
	return (0);
}

char	*get_envp_value(t_envp *envp, char *key)
{
	if (!key)
		return (NULL);
	while (envp)
	{
		if (envp->key && ft_strncmp(key, envp->key, ft_strlen(key)) == 0)
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}

int	go_to_path_home(char *path, t_envp *envp)
{
	char	*home;
	char	*res;

	home = get_envp_value(envp, HOME);
	if (home == NULL)
	{
		write(2, "minishell: cd: HOME not set\n", 28);
		return (1);
	}
	res = ft_strjoin(home, path + 1);
	if (chdir(res) == -1)
	{
		ft_perror(res);
		return (1);
	}
	return (0);
}
