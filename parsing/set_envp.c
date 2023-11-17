/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoson <seoson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:20:28 by seoson            #+#    #+#             */
/*   Updated: 2023/11/15 11:29:04 by seoson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	make_envp_cmd(t_envp *envp_list, char **str)
{
	t_envp	*envp;

	envp = (t_envp *)malloc(sizeof(t_envp));
	envp->key = ft_strdup(str[0]);
	envp->value = ft_strdup(str[1]);
	envp->next = NULL;
	envp->have_equal = 1;
	if (envp_list->next == NULL)
		envp_list->next = envp;
	else
	{
		envp_list = envp_list->next;
		while (envp_list->next != NULL)
			envp_list = envp_list->next;
		envp_list->next = envp;
	}
}

static int	len_word(char const *s, char c)
{
	int	save;

	save = 0;
	while (*s)
	{
		if (*s == c)
			break ;
		s++;
		save++;
	}
	return (save);
}

char	**ft_split_equal(char *s)
{
	int		str_index;
	char	**str;

	str_index = len_word(s, '=');
	str = (char **)malloc(sizeof(char *) * (3));
	str[0] = ft_substr(s, 0, str_index);
	str[1] = ft_substr(s, str_index + 1, ft_strlen(s) - str_index);
	str[2] = 0;
	return (str);
}

void	set_envp(char **envp, t_envp *envp_list)
{
	int		envp_index;
	char	**split_str;

	envp_index = 0;
	envp_list->next = NULL;
	while (envp[envp_index])
	{
		split_str = ft_split_equal(envp[envp_index]);
		make_envp_cmd(envp_list, split_str);
		free_str(split_str);
		envp_index++;
	}
}
