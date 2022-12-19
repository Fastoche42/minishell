/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:42:01 by fl-hote            #+#    #+#             */
/*   Updated: 2022/12/07 08:03:59 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**exec_export_2(t_var *shell, char **var, char **tmp)
{
	char	**tab;
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 1;
	tab = ft_split(shell->input, ' ');
	str = modif_input(tab[j]);
	while (var[i])
	{
		tmp[i] = var[i];
		i++;
	}
	tmp[i] = ft_strdup(str);
	return (tmp);
}

int	exec_export(t_var *shell, char **var)
{
	char	**tmp;
	int		i;

	i = 0;
	if (check_export(shell->input))
		return (error_manager(4));
	tmp = malloc((ft_nb_lines_tab(var) + 1) * sizeof(char *));
	tmp = exec_export_2(shell, var, tmp);
	free(var);
	var = malloc((ft_nb_lines_tab(tmp)) * sizeof(char *));
	while (tmp[i])
	{
		var[i] = tmp[i];
		i++;
	}
	free(tmp);
	return (0);
}
