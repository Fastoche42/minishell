/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:08:34 by mfusil            #+#    #+#             */
/*   Updated: 2022/12/07 08:03:59 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_echo_n(t_var *shell)
{	
}

void	exec_echo_spaces(t_var *shell)
{
	char	**tab;
	int		i;

	tab = ft_split(shell->input, ' ');
	i = 1;
	while (tab[i])
	{
		ft_putstr(tab[i]);
		i++;
		if (tab[i])
			write(1, " ", 1);
	}
}

void	exec_echo_quotes(t_var *shell)
{
	char	**tab;
	int		i;

	tab = ft_split(shell->input, '\"');
	i = 1;
	while (tab[i])
	{
		ft_putstr(tab[i]);
		i++;
	}
}

void	exec_echo(t_var *shell)
{
	char	*str;
	char	**tab;
	int		i;

	i = 0;
	while (shell->input[i])
	{
		if (shell->input[i] == '\"')
		{
			exec_echo_quotes(shell);
			break ;
		}
		else if (shell->input[i] != '\"' && shell->input[i + 1] == '\0')
		{
			exec_echo_spaces(shell);
			break ;
		}
		/**else if (shell->input[i] == '-' && shell->input[i] == 'n')
		{
			exec_echo_n(shell);
			break ;
		}**/
		i++;
	}
	printf("\n");
}
