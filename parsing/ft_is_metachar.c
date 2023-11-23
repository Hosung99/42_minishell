/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_metachar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:40:11 by seoson            #+#    #+#             */
/*   Updated: 2023/11/23 16:11:32 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_quote(char curr)
{
	if (curr == '\'' || curr == '\"')
		return (SUCCESS);
	else
		return (FAILURE);
}

int	is_metachar(char curr)
{
	if (curr == '<' || curr == '>' || curr == ' ' || curr == '\t')
		return (SUCCESS);
	else
		return (FAILURE);
}
