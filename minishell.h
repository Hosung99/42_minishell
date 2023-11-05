/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:54:58 by seoson            #+#    #+#             */
/*   Updated: 2023/11/01 20:09:05 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "./libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_token t_token;
typedef struct s_redir t_redir;
typedef struct s_cmd t_cmd;
typedef struct s_envp t_envp;

struct	s_envp
{
	char	*key;
	char	*value;
	t_envp	*next;	
};

typedef enum e_token_identifier
{
	token_cmd,
	token_option,
	token_read_redir,
	token_heredoc,
	token_write_redir,
	token_append_redir,
} t_token_identifier;

struct  s_token
{
    char    *str;
    int     type;
	t_token *next;
};

struct s_redir
{
	char	*str;
	char    *filename;
	t_redir *next;
};

struct	s_cmd
{
	char	**cmd;
	t_redir	*redir;
	t_cmd	*next;
};

int		set_termios(struct termios *old_term, struct termios *new_term);
int 	reset_termios(struct termios *old_term);
int		print_picture(int argc, char **argv);
void 	parse(char *line, t_cmd **cmd, t_envp *envp_list);
void	sig_handler(int signo);
void	set_signal(void);
int		set_token_type(char *str);
void	set_envp(char **envp, t_envp *envp_list);
char	*ft_split_index(char *str, int before_index, int cur_index);
void	make_cmd_token(char *str, t_token *token_header,
	int *cur_index, int *before_index);
void	make_redir_token(char *str, t_token *token_header, int *cur_index, int *before_index);
void	make_quote_token(char *str, t_token *token, int *curr_index, int *before_index);
int		set_quote(t_token *token_header, t_envp *envp_list, t_cmd **cmd);
int		check_quote(t_token *token, t_envp *envp_list);
char	*ft_strtrim_index(char *str, char c);
char	*ft_search_envp_key(t_envp *envp_list, char *str);
void	set_cmd(t_token *token_header, t_cmd **cmd);
int		executor(t_cmd *cmd, t_envp *envp);

#endif