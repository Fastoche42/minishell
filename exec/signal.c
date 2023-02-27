/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:55:18 by fl-hote           #+#    #+#             */
/*   Updated: 2023/02/27 12:46:37 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		if (g_data.pid != 0)
		{
			kill(g_data.pid, SIGQUIT);
			rl_replace_line("", 0);
			printf("\n");
			rl_redisplay();
		}
		else
		{
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}
