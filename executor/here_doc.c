/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:16:13 by sgo               #+#    #+#             */
/*   Updated: 2023/11/17 16:45:53 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int		check_heredoc(t_cmd *cmd);
void	do_heredoc(t_cmd *cmd, char *filename);
char	*make_random_here_doc();

void	here_doc(t_redir *redir, char *filename)
{
	char	*tmp;
	char	*line;
	int		fd;

	unlink(filename);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 00000644);
	if (fd < 0)
		ft_perror("here_doc");
	while (1)
	{
		tmp = readline("> ");
		if (!tmp)
		{
			printf(">");
			break ;
		}
		line = ft_strjoin(tmp, "\n");
		if (!line)
			ft_perror("readline");
		if (ft_strncmp(redir->filename, tmp, ft_strlen(tmp) + 1) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		free(tmp);
		free(line);
	}
	free(tmp);
	free(line);
	close(fd);
}

void	open_here_docs(t_cmd *cmd)
{
	int		pid;
	char	*filename;
	t_cmd	*temp_cmd;

	temp_cmd = cmd;
	filename = NULL;
	set_signal(DEF, IGN);
	if (check_heredoc(cmd) != 1)
		return ;
	while (temp_cmd)
	{
		filename = make_random_here_doc();
		pid = fork();
		if (pid == 0)
		{
			do_heredoc(temp_cmd, filename);
			free(filename);
			exit(0);
		}
		else if (pid < 0)
			ft_perror("fork");
		else
		{
			waitpid(pid, &g_exit_status, 0);
			set_signal(IGN, IGN);
			temp_cmd->here_doc_fd = open(filename, O_RDONLY);
			if (cmd->here_doc_fd < 0)
				ft_perror("here_doc");
			unlink(filename);
		}
		free(filename);
		temp_cmd = temp_cmd->next;
	}
}

int	check_heredoc(t_cmd *cmd)
{
	t_cmd	*temp_cmd;
	t_redir	*temp_redir;

	temp_cmd = cmd;
	while (temp_cmd)
	{
		temp_redir = temp_cmd->redir;
		while (temp_redir)
		{
			if (ft_strncmp(temp_redir->str, "<<", 3) == 0)
				return (1);
			temp_redir = temp_redir->next;
		}
		temp_cmd = temp_cmd->next;
	}
	return (0);
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

char	*make_random_here_doc()
{
	char	*filename;
	char	*tmp;
	int		i;

	filename = ft_strdup(HERE_DOC_FILE);
	i = 0;
	while (i < 10)
	{
		tmp = ft_itoa(rand() % 10);
		filename = ft_strjoin_char(filename, tmp[0]);
		free(tmp);
		i++;
	}
	return (filename);
}
