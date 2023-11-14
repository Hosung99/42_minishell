/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:54:23 by sgo               #+#    #+#             */
/*   Updated: 2023/11/14 19:02:49 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int	g_exit_status;
int	only_number(char *str);

void	ft_exit(char **cmd, t_info *info)
{
	int	len;

	len = 0;
	while(cmd[len])
		len++;
	if (len > 1)
	{
		write(STDERR_FILENO, "exit\n", 5);
		write(STDERR_FILENO, "minishell: exit: too many arguments\n", 37);
		g_exit_status = 1;
		return ;
	}
	if (only_number(cmd[0]) == 0)
	{
		write(STDERR_FILENO, "exit\n", 5);
		write(STDERR_FILENO, "minishell: exit: ", 17);
		write(STDERR_FILENO, cmd[0], ft_strlen(cmd[0]));
		write(STDERR_FILENO, ": numeric argument required\n", 28);
		g_exit_status = 255;
		return ;
	}
	write(STDOUT_FILENO, "exit\n", 5);
	if (cmd[0])
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