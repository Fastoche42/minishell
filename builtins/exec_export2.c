/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:45:59 by event             #+#    #+#             */
/*   Updated: 2023/02/27 12:46:08 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_export2(char **tmp, t_var *shell)
{
	if (!check_export(tmp, shell))
	{
		if (change_export(tmp, shell))
		{
			free_strs(NULL, tmp);
			return (1);
		}
	}
	else if (new_export(tmp, shell))
	{
		free_strs(NULL, tmp);
		return (1);
	}
	free_strs(NULL, tmp);
	return (0);
}
