/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 11:15:12 by sgo               #+#    #+#             */
/*   Updated: 2023/11/09 01:15:53 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

#include "../minishell.h"
#include <fcntl.h>
#include <sys/wait.h>

# define HERE_DOC_FILE ".here_doc"

typedef	struct	s_info
{
	char	**cmd_path;
	char	*cmd;
	int		pipe_fd[2];
	int		tmp_fd;
	int		outfile_fd;
	t_cmd	*cmd_start;
	t_envp	*envp_start;
	pid_t	pid;
	int		status;
	int		cmd_cnt;
	int		have_outfile;
}				t_info;

void	init_info(t_info *info, t_envp *envp, t_cmd *cmd);
void	builtin(t_cmd *cmd, t_info *info, t_envp *envp);
int		is_builtin(char *cmd);
void	child_process(t_cmd *cmd, t_info *info);
void	parent_process(t_info *info);
void	dup_stdout(t_info *info, t_cmd *cmd);
int		check_slash(char *cmd);
void	exit_perror(char *msg);
char	**find_path(t_envp *envp, char *key);
char	*get_cmd(char **path, char *cmd);
void	wait_all(t_info *info);
void	file_open(t_cmd *cmd, t_info *info);
int		cmd_cnt(t_cmd *cmd);
void	here_doc(t_redir *redir, t_info *info);
void	free_envp(t_envp *envp);
void	free_info(t_info *info);

#endif