/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:55:18 by fl-hote            #+#    #+#             */
/*   Updated: 2022/12/07 15:04:20 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_pid = 0;

void	handler_sig(int signum)
{
	if (g_pid) // ?
		return ;
	if (signum == SIGINT) //ctrl c
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGQUIT) //ctrl d (?)(ctrl D devrait juste exit, non ?)
	{
		/*
		rl_on_new_line();
		rl_redisplay();
		printf("  \b\b");
		*/
		printf("exit\n");
		exit(0);
	}
}
