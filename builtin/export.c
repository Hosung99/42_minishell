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
void	set_key_value(t_envp *envp, char *input_key, char *input_value);

void	ft_export(char **cmd, t_envp *envp)
{
	int		index;
	int		char_index;
	char	*input_key;
	char	*input_value;
	
	index = 0;
	while (cmd[index])
	{
		char_index = 0;
		if (cmd[index][0] == '=' || !ft_isalpha(cmd[index][0]))
			print_export_err(cmd[index]);
		else
		{
			while (cmd[index][char_index] != '=')
				char_index++;
			input_key = ft_substr(cmd[index], 0, char_index);
			input_value = ft_substr(cmd[index], char_index + 1, ft_strlen(cmd[index]));
			set_key_value(envp, input_key, input_value);
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

void	set_key_value(t_envp *envp, char *input_key, char *input_value)
{
	t_envp	*tmpenv;

	tmpenv = envp;
	while (tmpenv)
	{
		if (ft_strncmp(tmpenv->key, input_key, ft_strlen(tmpenv->key) + 1) == 0)
		{
			free(tmpenv->value);
			tmpenv->value = input_value;
			free(input_key);
			return ;
		}
		tmpenv = tmpenv->next;
	}
	tmpenv = envp;
	while (tmpenv->next)
		tmpenv = tmpenv->next;
	tmpenv->next = (t_envp *)malloc(sizeof(t_envp));
	tmpenv->next->key = input_key;
	tmpenv->next->value = input_value;
	tmpenv->next->next = NULL;	
}
