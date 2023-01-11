/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 16:45:59 by fl-hote           #+#    #+#             */
/*   Updated: 2022/12/19 16:47:36 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_unset(char *tmp, t_env *env)
{
	t_env	*ptr;

	ptr = env;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, tmp))
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

static int	change_unset(char *tmp, t_env *env)
{
	t_env	*ptr;

	ptr = env;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, tmp))
		{
			ptr->exists = 0;
			return (0);
		}
		ptr = ptr->next;
	}
	return (1);
}

int    exec_unset(t_cmdlist *cmd, t_env *env)
{
    int		i;
	char	*tmp;

	i = 1;
	while (cmd->cmd_arg[i])
	{
		tmp = ft_strdup(cmd->cmd_arg[i]);
		if (!tmp)
			return (1);
		if (check_unset(tmp, env))
			if (change_unset(tmp, env))
				return (1);
		free (tmp);
		i++;
	}
	return (0);
}