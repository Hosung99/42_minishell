/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_index.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:58:42 by seoson            #+#    #+#             */
/*   Updated: 2023/11/06 15:35:59 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_split_index(char *str, int before_index, int cur_index)
{
	int		new_str_index;
	char	*new_str;

	new_str_index = 0;
	new_str = (char *)malloc(sizeof(char) * (cur_index - before_index + 2)); // 수정했어잉
	if (!str)
		return (NULL);
	while (before_index <= cur_index) //애매해잉
	{
		if (str[before_index] == ' ' || str[before_index] == '\t')
			before_index++;
		else
			new_str[new_str_index++] = str[before_index++];
	}
	new_str[new_str_index] = '\0';
	return (new_str);
}
