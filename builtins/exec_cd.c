/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:47:59 by fl-hote            #+#    #+#             */
/*   Updated: 2022/12/07 08:03:59 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	update_pwd(t_cmdlist *cmd, t_env *env)
{
	//int		i;
	t_env	*ptr;
	char 	*tmp;

	//i = 0;
	ptr = env;
	while (env)
	{
		if (ft_strcmp(env->name, "PWD") == 0)
			{
				tmp = ft_strdup(env->value);
				free(env->value);
				env->value = getcwd(NULL, 0); //à adapter pour le cas des chemins relatifs
				if (!tmp || !env->value)
					return (1);
			}
		if (ft_strcmp(env->name, "OLDPWD") == 0)
		{
			free(env->value);
			env->value = ft_strdup(tmp);
			if (!env->value)
				return (1);
		}
		env = env->next;
	}
	env = ptr;
	free(tmp);
	return (0);
}

int	exec_cd(t_cmdlist *cmd, t_env *env)
{
	t_env *ptr;

	ptr = env;
	if (*cmd->cmd_arg[1] == '-')
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
	else
	{
		if (chdir(cmd->cmd_arg[1]) != 0)
			return (1);
	}
	if (update_pwd(cmd, env))
		return (1);
	return (0);
}
