/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_handler2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorber <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:33:38 by jlorber           #+#    #+#             */
/*   Updated: 2023/02/27 14:33:40 by jlorber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	var_handler(t_cmdlist *cmd, t_var *shell)
{
	char	**tmp;
	int		i;

	i = 0;
	while (cmd->cmd_arg[i])
	{
		if (ft_strchr(cmd->cmd_arg[i], '=') != NULL)
		{
			tmp = ft_split(cmd->cmd_arg[i], '=');
			if (!tmp)
				return (1);
			if (var_handler2(tmp, shell))
				return (1);
		}
		i++;
	}
	return (0);
}
