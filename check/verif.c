/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:08:57 by mfusil            #+#    #+#             */
/*   Updated: 2022/12/06 10:47:09 by mfusil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	verif(t_var *shell, char **var)
{
	int	error;

	error = check_path_cmd(shell, var);
	if (error)
		error_manager(error);
	return (0);
}
