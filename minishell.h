/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:54:58 by seoson            #+#    #+#             */
/*   Updated: 2023/11/15 20:06:59 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_token	t_token;
typedef struct s_redir	t_redir;
typedef struct s_cmd	t_cmd;
typedef struct s_envp	t_envp;

struct s_envp
{
	char	*key;
	char	*value;
	int		have_equal;
	t_envp	*next;
};

typedef enum e_token_identifier
{
	TOKEN_WORD,
	TOKEN_READ_REDIR,
	TOKEN_HEREDOC,
	TOKEN_WRITE_REDIR,
	TOKEN_APPEND_REDIR,
	TOKEN_S_QUOTE,
	TOKEN_D_QUOTE,
}	t_token_identifier;

struct s_token
{
	char	*str;
	int		type;
	t_token	*next;
};

struct s_redir
{
	char	*str;
	char	*filename;
	t_redir	*next;
};

struct s_cmd
{
	char	**cmd;
	t_redir	*redir;
	t_cmd	*next;
};

int		set_termios(struct termios *old_term, struct termios *new_term);
int		reset_termios(struct termios *old_term);
int		print_picture(int argc, char **argv);
int		parse(char *line, t_cmd **cmd, t_envp *envp_list);
void	sig_handler(int signo);
void	set_signal(char *str);
int		set_token_type(char *str);
void	set_envp(char **envp, t_envp *envp_list);
char	*ft_split_index(char *str, int before_index, int cur_index);
int		make_cmd_token(char *str, t_token *token_header, int curr_index);
int		make_redir_token(char *str, t_token *token_header, int curr_index);
int		do_tokenize(char **pipe_split_line, int pipe_index, t_cmd **cmd, t_envp *envp_list);
char	**ft_split_pipe(char *str, int *pipe_cnt);
void	make_cmd(t_token *token_header, t_cmd **cmd, int *option_cnt);
void	malloc_cmd(t_token *token_header, t_cmd **cmd);
int 	is_metachar(char curr);
void	set_token_position(t_token *token_header, t_token *new_token);
int		set_quote(t_token *token_header, t_envp *envp_list, t_cmd **cmd);
void	change_envp_var(t_token *token, t_envp *envp_list);
void	check_dollar(char **save_str, char *str, int *str_index, t_token *token, t_envp *envp_list);
char	*ft_strtrim_index(char *str, char c);
char	*ft_search_envp_key(t_envp *envp_list, char *str);
int		set_cmd(t_token *token_header, t_cmd **cmd);
int		executor(t_cmd *cmd, t_envp *envp);
void	free_cmd(t_cmd **cmd);
void	free_str(char **str);
void	free_redir(t_redir *redir);
void	free_token(t_token *token_header);
char	*ft_strjoin_char(char *str, char c);
int		check_in_quote(char *str, int str_index);
int		check_in_d_quote(char *str, int str_index);
void	delete_quote(t_token *token);
int		before_check_pipe(char *line);
int		before_check_redir(char *str);
int		before_check_quote(char *line);
void	update_shlvl(t_envp *envp);

#endif
