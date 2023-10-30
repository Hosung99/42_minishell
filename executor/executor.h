/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 11:15:12 by sgo               #+#    #+#             */
/*   Updated: 2023/10/31 01:26:12 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

#include "../minishell.h"
#include <fcntl.h>
#include <sys/wait.h>

typedef	struct	s_info
{
	char	**cmd_path;
	char	*cmd;
	int		pipe_fd[2];
	int		tmp_fd;
	int		outfile_fd;
	int		cnt;
	pid_t	pid;
	int		status;
}				t_info;

void	init_info(t_info *info, t_envp *envp);
void	builtin(t_cmd *cmd, t_info *info, t_envp *envp);
int		is_builtin(char *cmd);
void	child_process(t_cmd *cmd, t_info *info);
void	parent_process(t_info *info);
void	dup_stdout(t_info *info, t_cmd *cmd);
int		check_slash(char *cmd);
void	exit_perror(char *msg);
char	**find_path(t_envp *envp);
char	*get_cmd(char **path, char *cmd);
void	wait_all(t_info *info);
void	file_open(t_cmd *cmd, t_info *info);

#endif