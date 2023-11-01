/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 17:25:27 by seoson            #+#    #+#             */
/*   Updated: 2023/10/31 21:42:54 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tokenize(char *str, t_cmd **cmd, t_envp *envp_list)
{
	t_token	*token_header;
	int		curr_index;
	int		before_index;

	token_header = (t_token *)malloc(sizeof(t_token)); //null guard여지
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
		curr_index++;
	}
	if (set_quote(token_header->next, envp_list, cmd) == -1)
		return ;
}

void	parse(char *line, t_cmd *cmd, t_envp *envp_list)
{
	char	**pipe_split_line;
	int		pipe_cnt;
	int		pipe_index;

	pipe_cnt = 0;
	pipe_index = -1;
	pipe_split_line = ft_split(line, '|', &pipe_cnt);
	cmd = NULL;
	while (++pipe_index < pipe_cnt)
		tokenize(pipe_split_line[pipe_index], &cmd, envp_list);
	free(pipe_split_line);
	return ;
}
		