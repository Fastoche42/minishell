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

int	exec_cd(t_cmdlist *cmd, t_env *env)
{
	
	if (chdir(cmd->cmd_arg[1]) != 0)
		return (error_manager(9), ft_putendl_fd(strerror(errno), 2, 1));
	if (update_pwd(cmd, env))
		return (1);
	return (0);
}

int	update_pwd(t_cmdlist * cmd, t_env *env)
{
	int		i;
	t_env	*ptr;
	char 	*tmp;

	i = 0;
	ptr = env;
	while (env)
	{
		if (ft_strcmp(env->name, "PWD") == 0)
			{
				tmp = ft_strdup(env->value);
				free(env->value);
				env->value = ft_strdup(cmd->cmd_arg[1]); //à adapter pour le cas des chemins relatifs
				if (!tmp || !env->value)
					return (1);
			}
		if (ft_strcmp(env->name, "OLDPWD"))
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