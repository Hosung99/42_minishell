/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:16:13 by sgo               #+#    #+#             */
/*   Updated: 2023/11/15 20:57:34 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	here_doc(t_redir *redir, t_info *info)
{
	int		file;
	char	*tmp;
	char	*line;

	unlink(HERE_DOC_FILE);
	file = open(HERE_DOC_FILE, O_CREAT | O_WRONLY | O_TRUNC, 00000644);
	if (file < 0)
		exit_perror("here_doc", info);
	while (1)
	{
		tmp = readline("> ");
		line = ft_strjoin(tmp, "\n");
		if (!line)
			break ;
		if (ft_strncmp(redir->filename, line, ft_strlen(line) + 1) == 0)
			break ;
		write(file, line, ft_strlen(line));
		free(tmp);
		free(line);
	}
	free(tmp);
	free(line);
	close(file);
	info->tmp_fd = open(HERE_DOC_FILE, O_RDONLY);
	if (info->tmp_fd < 0)
		exit_perror("here_doc", info);
	unlink(HERE_DOC_FILE);
}
