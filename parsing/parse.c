/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:25:27 by seoson            #+#    #+#             */
/*   Updated: 2023/11/06 15:40:58 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_token(t_token *token_header)
{
    t_token *token_header_temp;

    while (token_header)
    {
        token_header_temp = token_header;
        token_header = token_header->next;
		if (!token_header_temp->str)
       		free(token_header_temp->str);
		if (!token_header_temp)
        	free(token_header_temp);
    }
}

int	tokenize(char *str, t_cmd **cmd, t_envp *envp_list)
{
	t_token	*token_header;
	int		curr_index;
	int		before_index;

	token_header = (t_token *)malloc(sizeof(t_token));
	curr_index = 0;
	while (str[curr_index] == ' ' || str[curr_index] == '\t')
		curr_index++;
	before_index = curr_index;
	while (str[curr_index] && str)
	{
		if (str[curr_index] == '\'' || str[curr_index] == '"')
			make_quote_token(str, token_header, &curr_index, &before_index);
		else if (str[curr_index + 1] == '\0' || str[curr_index] == ' ' || str[curr_index] == '\t')
			make_cmd_token(str, token_header, &curr_index, &before_index);
		else if (str[curr_index] == '>' || str[curr_index] == '<')
			make_redir_token(str, token_header, &curr_index, &before_index);
		if (str[curr_index] != '\0')
			curr_index++;
	}
	if (set_quote(token_header->next, envp_list, cmd) == -1)
	{
		free_token(token_header);
		return (-1);
	}
	free_token(token_header);
	return (1);
}

void	parse(char *line, t_cmd **cmd, t_envp *envp_list)
{
	char	**pipe_split_line;
	int		pipe_cnt;
	int		pipe_index;

	pipe_cnt = 0;
	pipe_index = -1;
	pipe_split_line = ft_split(line, '|', &pipe_cnt);
	*cmd = NULL;
	while (++pipe_index < pipe_cnt)
		if (tokenize(pipe_split_line[pipe_index], cmd, envp_list) == -1)
			return ;
	free(pipe_split_line);
	return ;
}
