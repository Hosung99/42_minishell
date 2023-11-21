/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 21:41:35 by sgo               #+#    #+#             */
/*   Updated: 2023/11/21 19:44:47 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	ft_perror(char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	perror(msg);
	g_exit_status = EXIT_FAILURE;
}

void	ft_cmd_error(char *cmd)
{
	if (!cmd)
		return ;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	g_exit_status = EXIT_NOT_CMD;
	exit(EXIT_NOT_CMD);
}

void	ft_permission_error(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	g_exit_status = EXIT_FAILURE;
	exit(EXIT_FAILURE);
}

void	ft_heredoc_error(t_info *info)
{
	ft_putstr_fd("minishell: maximum here-document count exceeded\n", 2);
	g_exit_status = 2;
	exit_free(info);
}

void	ft_no_file_dir(char *cmd, t_info *info)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	g_exit_status = EXIT_NOT_CMD;
	exit_free(info);
}
