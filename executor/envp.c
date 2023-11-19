/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:15:14 by sgo               #+#    #+#             */
/*   Updated: 2023/11/18 19:00:35 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int		envp_cnt(t_envp *envp);
char	*input_envp(char *envp_key, char *envp_value);

char	**get_envp(t_envp *envp)
{
	char	**env_arr;
	int		i;

	i = 0;
	env_arr = (char **)malloc(sizeof(char *) * (envp_cnt(envp) + 1));
	if (env_arr == NULL)
		return (NULL);
	while (envp)
	{
		if (envp->key != NULL)
		{
			env_arr[i] = input_envp(envp->key, envp->value);
			if (env_arr[i] == NULL)
				return (NULL); // return 전에 모든 env_arr[i] free
			envp = envp->next;
			i++;
		}
	}
	env_arr[i] = NULL;
	return (env_arr);
}

char	*input_envp(char *envp_key, char *envp_value)
{
	char	*key;
	char	*tmp_arr;

	key = ft_strjoin(envp_key, "=");
	if (key == NULL)
		return (NULL);
	if (envp_value == NULL)
		tmp_arr = ft_strdup(key);
	else
		tmp_arr = ft_strjoin(key, envp_value);
	ft_free(key);
	if (tmp_arr == NULL)
		return (NULL);
	return (tmp_arr);
}

int	envp_cnt(t_envp *envp)
{
	int	cnt;

	cnt = 0;
	while (envp)
	{
		if (envp->key != NULL)
			cnt++;
		envp = envp->next;
	}
	return (cnt);
}

void	update_shlvl(t_envp *envp)
{
	char	*tmp;

	envp = envp->next;
	while (envp)
	{
		if (strncmp(envp->key, "SHLVL", 6) == 0)
		{
			if (envp->value == NULL)
				envp->value = ft_strdup("1");
			else
			{
				tmp = envp->value;
				envp->value = ft_itoa(ft_atoi(envp->value) + 1);
				free(tmp);
			}
			break ;
		}
		envp = envp->next;
	}
}
