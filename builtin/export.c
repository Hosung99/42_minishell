/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgo <sgo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 16:55:02 by sgo               #+#    #+#             */
/*   Updated: 2023/11/14 16:32:46 by sgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	print_export_err(char *cmd);
void	set_key_value(t_envp *envp, char *input_key, char *input_value, int have_equal);
void	ft_env_export(t_envp *envp);

void	ft_export(char **cmd, t_envp *envp)
{
	int		index;
	int		char_index;
	char	*input_key;
	char	*input_value;
	int		have_equal;
	
	index = 0;
	if (cmd[0] == NULL)
	{
		ft_env_export(envp);
		return ;
	}
	while (cmd[index])
	{
		have_equal = 0;
		char_index = 0;
		if (cmd[index][0] == '=' || !ft_isalpha(cmd[index][0]))
			print_export_err(cmd[index]);
		else
		{
			while (cmd[index][char_index] != '=' && cmd[index][char_index] != '\0')
				char_index++;
			if (cmd[index][char_index] == '=')
				have_equal = 1;
			input_key = ft_substr(cmd[index], 0, char_index);
			input_value = ft_substr(cmd[index], char_index + 1, ft_strlen(cmd[index]));
			set_key_value(envp, input_key, input_value, have_equal);
		}
		index++;
	}
}

void	print_export_err(char *cmd)
{
	write(STDERR_FILENO, "minishell: export: `", 20);
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, "': not a valid identifier\n", 26);
}

void	set_key_value(t_envp *envp, char *input_key, char *input_value, int have_equal)
{
	t_envp	*tmpenv;

	tmpenv = envp;
	while (tmpenv)
	{
		if (tmpenv->key != NULL && ft_strncmp(tmpenv->key, input_key, ft_strlen(input_key) + 1) == 0)
		{
			ft_free(tmpenv->value);
			tmpenv->value = input_value;
			tmpenv->have_equal = have_equal;
			ft_free(input_key);
			return ;
		}
		tmpenv = tmpenv->next;
	}
	tmpenv = envp;
	while (tmpenv->next)
		tmpenv = tmpenv->next;
	tmpenv->next = (t_envp *)malloc(sizeof(t_envp));
	tmpenv->next->key = input_key;
	tmpenv->next->have_equal = have_equal;
	tmpenv->next->value = input_value;
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
		if (tmpenv->have_equal == 1)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(tmpenv->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		tmpenv = tmpenv->next;
	}
}
