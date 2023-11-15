/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:59:15 by seoson            #+#    #+#             */
/*   Updated: 2023/11/14 22:14:28 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_status;

void	change_str(char	**new_str, char *envp_key)
{
	int		envp_key_index;
	char	*temp_str;

	envp_key_index = 0;
	while (envp_key && envp_key[envp_key_index])
	{
		temp_str = *new_str;
		*new_str = ft_strjoin_char(*new_str, envp_key[envp_key_index]);
		envp_key_index++;
	}
}

void	check_envp(char **new_str, \
	t_token *token, int *str_index, t_envp *envp_list)
{
	int		temp_index;
	char	*envp_key;

	temp_index = *str_index;
	while (token->str && token->str[(*str_index)++])
		if (ft_isalnum(token->str[(*str_index)]) == 0)
			break ;
	envp_key = ft_search_envp_key(envp_list, \
		ft_split_index(token->str, temp_index + 1, (*str_index) - 1));
	change_str(new_str, envp_key);
	free(envp_key);
}

void	change_envp_var(t_token *token, t_envp *envp_list)
{
	char	*save_str;
	char	*temp_str;
	char	*str;
	int		str_index;

	str = token->str;
	str_index = 0;
	save_str = ft_strdup("");
	while (str && str[str_index])
	{
		if (str[str_index] == '$')
			check_envp(&save_str, token, &str_index, envp_list);
		else
		{
			temp_str = save_str;
			save_str = ft_strjoin_char(save_str, str[str_index]);
			str_index++;
		}
	}
	free(token->str);
	token->str = save_str;
}

int	set_quote(t_token *token_header, t_envp *envp_list, t_cmd **cmd)
{
	t_token	*token_temp;

	token_temp = token_header;
	(void)cmd;
	while (token_temp)
	{
		if (token_temp->type == TOKEN_D_QUOTE || token_temp->type == TOKEN_WORD)
			change_envp_var(token_temp, envp_list);
		token_temp = token_temp->next;
	}
	if (set_cmd(token_header, cmd) == -1)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		g_exit_status = 258;
		return (-1);
	}
	return (1);
}
