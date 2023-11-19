/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:16:13 by sgo               #+#    #+#             */
/*   Updated: 2023/11/19 17:01:10 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	do_heredoc(t_cmd *cmd, char *filename);
void	here_doc_fork(t_cmd *temp_cmd, char *filename);

void	here_doc(t_redir *redir, char *filename)
{
	char	*tmp;
	char	*line;
	int		fd;

	unlink(filename);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 00000644);
	if (fd < 0)
		ft_perror("here_doc");
	line = NULL;
	while (1)
	{
		tmp = get_readline();
		line = ft_strjoin(tmp, "\n");
		if (!line)
			ft_perror("readline");
		if (ft_strncmp(redir->filename, tmp, ft_strlen(tmp) + 1) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		ft_free(tmp);
		ft_free(line);
	}
	ft_free(tmp);
	ft_free(line);
	close(fd);
}

void	open_here_docs(t_cmd *cmd)
{
	char	*filename;
	t_cmd	*temp_cmd;
	int		index;

	temp_cmd = cmd;
	filename = NULL;
	index = 0;
	if (check_heredoc(cmd) != 1)
		return ;
	set_signal(IGN, IGN);
	while (temp_cmd)
	{
		printf("cmd\n");
		filename = make_random_here_doc(index);
		here_doc_fork(temp_cmd, filename);
		ft_free(filename);
		temp_cmd = temp_cmd->next;
		index++;
	}
	set_signal(TER, TER);
}

void	here_doc_fork(t_cmd *temp_cmd, char *filename)
{
	int	pid;
	
	pid = fork();
	if (pid == 0)
	{
		set_signal(CHI, IGN);
		do_heredoc(temp_cmd, filename);
		ft_free(filename);
		exit(0);
	}
	else if (pid < 0)
		ft_perror("fork");
	else
	{
		waitpid(pid, &g_exit_status, 0);
		temp_cmd->here_doc_fd = open(filename, O_RDONLY);
		if (temp_cmd->here_doc_fd < 0)
			ft_perror("here_doc");
		unlink(filename);
	}
}


void	do_heredoc(t_cmd *cmd, char *filename)
{
	t_redir	*temp_redir;

	if (cmd->redir == NULL)
		return ;
	temp_redir = cmd->redir;
	while (temp_redir)
	{
		if (ft_strncmp(temp_redir->str, "<<", 3) == 0)
			here_doc(temp_redir, filename);
		temp_redir = temp_redir->next;
	}
	return ;
}
