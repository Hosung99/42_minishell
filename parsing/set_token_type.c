/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:26:44 by seoson            #+#    #+#             */
/*   Updated: 2023/11/14 22:00:58 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_token_type(char *str)
{
	int	index;

	index = 0;
	while (str && str[index])
	{
		if (str[index] == '"')
			return (TOKEN_D_QUOTE);
		else if (str[index] == '\'')
			return (TOKEN_S_QUOTE);
		else if (str[index] == '>')
			return (TOKEN_READ_REDIR);
		else if (str[index] == '<')
			return (TOKEN_WRITE_REDIR);
		index++;
	}
	return (TOKEN_WORD);
}
