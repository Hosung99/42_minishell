/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:48:06 by seoson            #+#    #+#             */
/*   Updated: 2023/11/14 14:48:38 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin_char(char *str, char c)
{
	char	*new_str;
	int		str_index;

	str_index = 0;
	if (str != NULL)
		new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) + 2));
	else
		new_str = (char *)malloc(sizeof(char) * 2);
	while (str && str[str_index])
	{
		new_str[str_index] = str[str_index];
		str_index++;
	}
	new_str[str_index++] = c;
	new_str[str_index] = '\0';
	free(str);
	return (new_str);
}
