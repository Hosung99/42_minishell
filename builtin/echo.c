/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:54:20 by sgo               #+#    #+#             */
/*   Updated: 2023/11/22 19:37:50 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	is_option_n(char *str, int *isoption_n);

void	ft_echo(char **args)
{
	int	i;
	int	isoption_n;

	i = 0;
	isoption_n = 0;
	while (args[i] && is_option_n(args[i], &isoption_n))
		i++;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (isoption_n == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

int	is_option_n(char *str, int *isoption_n)
{
	int	have_n;

	have_n = 0;
	if (*str != '-')
		return (0);
	str++;
	while (*str)
	{
		if (*str != 'n')
			return (0);
		have_n = 1;
		*isoption_n = 1;
		str++;
	}
	if (have_n)
		return (1);
	return (0);
}
