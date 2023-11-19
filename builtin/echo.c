/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:54:20 by sgo               #+#    #+#             */
/*   Updated: 2023/11/17 17:46:16 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	is_option_n(char *str, int *isoption_n);

void	echo(char **args)
{
	int	i;
	int	isoption_n;

	i = 0;
	isoption_n = 0;
	while (args[i] && is_option_n(args[i], &isoption_n))
		i++;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (isoption_n == 0)
		ft_putchar_fd('\n', 1);
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
