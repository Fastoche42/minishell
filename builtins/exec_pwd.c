/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:12:08 by fl-hote            #+#    #+#             */
/*   Updated: 2022/12/07 08:24:10 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_pwd(t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->name, "PWD"))
		{
			printf("%s\n", env->value);
			return (0);
		}
		env = env->next;
	}
	return (1);
}