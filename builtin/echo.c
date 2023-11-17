/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:54:20 by sgo               #+#    #+#             */
/*   Updated: 2023/11/11 17:50:16 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	isOptionN(char *str, int* isOptionN);

void	echo(char **args)
{
	int	i;
	int	isoptionN;

	i = 0;
	isoptionN = 0;
	while (args[i] && isOptionN(args[i], &isoptionN))
		i++;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (isoptionN == 0)
		ft_putchar_fd('\n', 1);
}

int	isOptionN(char *str, int *isoptionN)
{
	int	isOptionN;

	isOptionN = 0;
	if (*str != '-')
		return (0);
	str++;
	while (*str)
	{
		if (*str != 'n')
			return (0);
		isOptionN = 1;
		*isoptionN = 1;
		str++;
	}
	if (isOptionN)
		return (1);
	return (0);
}
