/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 11:15:12 by sgo               #+#    #+#             */
/*   Updated: 2023/11/23 21:15:15 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../minishell.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>

# define HERE_DOC_FILE ".here_doc"
# define SHLVL "SHLVL"
# define DO_HERE_DOC 0
# define CHECK_HERE_DOC 1

extern int	g_exit_status;

typedef struct s_info
{
	char		**cmd_path;
	char		*cmd;
	int			pipe_fd[2];
	int			tmp_fd;
	int			outfile_fd;
	int			stdout_fd;
	t_cmd		*cmd_start;
	t_envp		*envp_start;
	pid_t		pid;
	int			status;
	int			cmd_cnt;
	int			have_outfile;
	int			errono;
	int			here_doc_cnt;
}				t_info;

void	init_info(t_info *info, t_envp *envp, t_cmd *cmd);
void	builtin(t_cmd *cmd, t_info *info, t_envp *envp);
int		is_builtin(char *cmd);
void	child_process(t_cmd *cmd, t_info *info, t_envp *envp);
void	parent_process(t_info *info);
void	dup_stdout(t_info *info, t_cmd *cmd);
int		check_slash(char *cmd, t_info *info);
void	exit_perror(char *msg, t_info *info);
char	**find_path(t_envp *envp);
char	*get_cmd(char **path, char *cmd, t_info *info);
void	wait_all(t_cmd	*cmd);
int		file_open(t_cmd *cmd, t_info *info);
int		cmd_cnt(t_cmd *cmd);
void	here_doc(t_redir *redir, char *filename);
void	free_info(t_info *info);
void	open_here_docs(t_info *info, t_cmd *cmd);
char	*make_random_here_doc(int index);
int		check_heredoc(t_cmd *cmd);
int		have_here_doc(t_cmd *cmd);
void	dup_stdout_builtin(t_info *info, t_cmd *cmd);

void	ft_perror(char *msg);
void	ft_cmd_error(char *cmd);
void	ft_permission_error(char *cmd);
char	**get_envp(t_envp *envp);
t_envp	*new_envp(char *key, char *value, int have_equal);
void	exit_free(t_info *info);
void	ft_free(void *ptr);
void	ft_heredoc_error(t_info *info);
void	ft_no_file_dir(char *cmd, t_info *info);

#endif