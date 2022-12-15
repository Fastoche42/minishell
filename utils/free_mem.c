/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:33:27 by mfusil            #+#    #+#             */
/*   Updated: 2022/12/11 18:25:19 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
}

void	free_mem(t_var *shell)
{
	//free_env(shell->env);
	free(shell);
}

int	ft_free_splited(char **str)
{
	int	i;

	if (str)
	{
		i = -1;
		while (str[++i])
			free (str[i]);
		free (str);
	}
	return (0);
}