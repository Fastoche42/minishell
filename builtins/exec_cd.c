/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:47:59 by fl-hote           #+#    #+#             */
/*   Updated: 2023/02/27 17:50:31 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	update_pwd(t_env *env)
{
	t_env	*ptr;
	char	*tmp;

	ptr = env;
	while (ptr)
	{
		if (ft_strcmp(ptr->name, "PWD") == 0)
		{
			tmp = ft_strdup(ptr->value);
			free_strs(ptr->value, NULL);
			ptr->value = getcwd(NULL, 0);
			if (!tmp || !ptr->value)
				return (1);
		}
		if (ft_strcmp(ptr->name, "OLDPWD") == 0)
		{
			free_strs(ptr->value, NULL);
			ptr->value = ft_strdup(tmp);
			if (!ptr->value)
				return (1);
		}
		ptr = ptr->next;
	}
	free_strs(tmp, NULL);
	return (0);
}

int	exec_cd(t_cmdlist *cmd, t_env *env)
{
	t_env	*ptr;

	ptr = env;
	if (cmd->cmd_arg[1] && *cmd->cmd_arg[1] == '-')
	{
		while (ptr)
		{
			if (!ft_strcmp("OLDPWD", ptr->name))
				cmd->cmd_arg[1] = ft_strdup(ptr->value);
			ptr = ptr->next;
		}
		if (!cmd->cmd_arg[1])
			return (1);
		if (chdir(cmd->cmd_arg[1]) != 0)
			return (1);
	}
	else if (chdir(cmd->cmd_arg[1]) != 0)
		return (1);
	if (update_pwd(env))
		return (1);
	return (0);
}
