/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:54:23 by sgo               #+#    #+#             */
/*   Updated: 2023/11/22 18:08:45 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	only_number(char *str);

void	ft_exit(char **cmd, t_info *info)
{
	int	len;

	len = 0;
	while (cmd[len])
		len++;
	write(STDOUT_FILENO, "exit\n", 5);
	if (only_number(cmd[0]) == 0)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd[0], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		g_exit_status = EXIT_NOT_NUM;
	}
	else if (len > 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		g_exit_status = EXIT_FAILURE;
		return ;
	}
	else if (cmd[0])
		g_exit_status = ft_atoi(cmd[0]) % 256;
	free_info(info);
	exit(g_exit_status);
}

int	only_number(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (1);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
