/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:50:58 by mfusil            #+#    #+#             */
/*   Updated: 2022/12/07 08:03:59 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exit_number_of_args(t_var *shell)
{
	char	**tab;
	int		i;
	int		args;

	i = 1;
	args = 0;
	tab = ft_split(shell->input, ' ');
	while (tab[i])
	{
		args++;
		i++;
	}
	return (args);
}

int	exec_exit(t_var *shell)
{
	int	args;
	int	exit_status;

	args = exit_number_of_args(shell);
	exit_status = 0;
	if (args > 0)
		return (write (1, "too many arguments\n", 19));
	else
	{
		write(1, "exit\n", 1); // why ?
		exit(exit_status);
		return (0);
	}
}
