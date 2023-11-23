/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:55:02 by sgo               #+#    #+#             */
/*   Updated: 2023/11/23 16:34:34 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	print_export_err(char *cmd);
void	set_key_value(t_envp *envp, char *key, char *value, int have_equal);
void	ft_env_export(t_envp *envp);
void	find_key_value(char *cmd, t_envp *envp);

void	ft_export(char **cmd, t_envp *envp)
{
	int		index;

	index = 0;
	if (cmd[0] == NULL)
	{
		ft_env_export(envp);
		return ;
	}
	while (cmd[index])
	{
		find_key_value(cmd[index], envp);
		index++;
	}
}

void	find_key_value(char *cmd, t_envp *envp)
{
	int		have_equal;
	int		char_index;
	char	*input_key;
	char	*input_value;

	have_equal = 0;
	char_index = 0;
	if (cmd[0] == '=' || !ft_isalpha(cmd[0]))
		print_export_err(cmd);
	else
	{
		while (cmd[char_index] != '=' \
			&& cmd[char_index] != '\0')
			char_index++;
		if (cmd[char_index] == '=')
			have_equal = 1;
		input_key = ft_substr(cmd, 0, char_index);
		input_value = ft_substr(cmd, char_index + 1, ft_strlen(cmd));
		set_key_value(envp, input_key, input_value, have_equal);
	}
}

void	print_export_err(char *cmd)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	g_exit_status = EXIT_FAILURE;
}

void	set_key_value(t_envp *envp, char *key, char *value, int have_equal)
{
	t_envp	*tmpenv;

	tmpenv = envp;
	while (tmpenv)
	{
		if (tmpenv->key && \
			ft_strncmp(tmpenv->key, key, ft_strlen(key) + 1) == 0)
		{
			ft_free(tmpenv->value);
			tmpenv->value = value;
			tmpenv->have_equal = have_equal;
			ft_free(key);
			return ;
		}
		tmpenv = tmpenv->next;
	}
	tmpenv = envp;
	while (tmpenv->next)
		tmpenv = tmpenv->next;
	tmpenv->next = (t_envp *)malloc(sizeof(t_envp));
	tmpenv->next->key = key;
	tmpenv->next->have_equal = have_equal;
	tmpenv->next->value = value;
	tmpenv->next->next = NULL;
}

void	ft_env_export(t_envp *envp)
{
	t_envp	*tmpenv;

	tmpenv = envp;
	while (tmpenv)
	{
		if (tmpenv->key != NULL)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(tmpenv->key, STDOUT_FILENO);
		}
		if (tmpenv->have_equal == 1 && tmpenv->value != NULL)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(tmpenv->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		if (tmpenv->key != NULL)
			ft_putstr_fd("\n", STDOUT_FILENO);
		tmpenv = tmpenv->next;
	}
}
