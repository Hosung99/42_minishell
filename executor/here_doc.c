/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:16:13 by sgo               #+#    #+#             */
/*   Updated: 2023/11/11 17:04:34 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	here_doc(t_redir *redir, t_info *info)
{
	int		file;
	char	*line;

	unlink(HERE_DOC_FILE);
	file = open(HERE_DOC_FILE, O_CREAT | O_WRONLY | O_TRUNC, 00000644);
	if (file < 0)
		exit_perror("here_doc", info);
	while (1)
	{
		line = readline("> ");
		if (!line)
			exit_perror("readline", info);
		if (ft_strncmp(redir->filename, line, ft_strlen(line) + 1) == 0)
			break ;
		write(file, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(file);
}
