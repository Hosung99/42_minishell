/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_index.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:58:42 by seoson            #+#    #+#             */
/*   Updated: 2023/11/11 14:50:59 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_split_index(char *str, int before_index, int cur_index)
{
	int		new_str_index;
	char	*new_str;

	new_str_index = 0;
	if (cur_index - before_index + 2 < 0)
		new_str = (char *)ft_calloc(1, sizeof(char) * 1);
	else
		new_str = (char *)malloc(sizeof(char) * (cur_index - before_index + 2));
	if (!str)
		return (NULL);
	while (before_index <= cur_index)
	{
		if (str[before_index] == ' ' || str[before_index] == '\t')
			before_index++;
		else
			new_str[new_str_index++] = str[before_index++];
	}
	new_str[new_str_index] = '\0';
	return (new_str);
}
