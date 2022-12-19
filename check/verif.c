/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:08:57 by fl-hote            #+#    #+#             */
/*   Updated: 2022/12/06 10:47:09 by fl-hote           ###   ########.fr       */
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
