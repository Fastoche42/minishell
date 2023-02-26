/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:27:00 by fl-hote           #+#    #+#             */
/*   Updated: 2022/12/07 08:03:59 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_env(t_env *env)
{
	char	**envp;
	int 	i;

	envp = build_envp(env);
	if (!envp)
		return (1);
	i = -1;
	while (envp[++i])
	{
		printf("%s\n", envp[i]);
	}
	free_strs(NULL, envp);
	return (0);
}
