/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 15:54:58 by seoson            #+#    #+#             */
/*   Updated: 2023/10/21 18:21:05 by seoson           ###   ########.fr       */
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

typedef struct s_redir t_redir;
typedef struct s_cmd t_cmd;

typedef struct  s_token
{
    char    *str;
    int     type;
}	t_token;

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

int	    set_termios(struct termios *old_term, struct termios *new_term);
int 	reset_termios(struct termios *old_term);
void	print_picture(void);
void	parse(char *line, t_cmd *cmd);
void	sig_handler(int signo);
void	set_signal(void);

#endif