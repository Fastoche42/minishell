/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:07:56 by fl-hote            #+#    #+#             */
/*   Updated: 2022/12/11 18:29:50 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_exit_code; 

static int	main_loop(t_var *shell, char *prompt)
{
	shell->input = readline(prompt);
	if (shell->input && *shell->input != 0)
	{
		add_history(shell->input);
		if (!parsing(shell))
		{
			if (!init_process(shell))
			{
				if (shell->cmd_nbr > 1 || (shell->cmd_nbr == 1
					&& !is_builtin(shell->cmdlist->cmd_arg[0])))
					g_exit_code = pipex(shell);
				else
					g_exit_code = one_cmd(shell);
			}
		}
		free_cmdlist(&(shell->cmdlist));
		reinit_struct(shell);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_var	*shell;

	g_exit_code = 0;
	if (argc != 1)
		return (error_manager(1));
	shell = init_struct(envp);
	if (!shell)
		return (error_manager(13));
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	shell->prompt = ft_strjoin(((*argv) + 2), "> ");
	while (1)
	{
		if (main_loop(shell, shell->prompt))
			break;
	}
	exit_minishell(shell, g_exit_code);
	return (0);
}
