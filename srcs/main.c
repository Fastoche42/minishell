/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorber <jlorber@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:07:56 by fl-hote           #+#    #+#             */
/*   Updated: 2023/02/28 17:08:20 by jlorber          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

struct s_data	g_data;

static int	main_loop(t_var *shell, char *prompt)
{
	t_var	*ptr;

	ptr = shell;
	shell->input = readline(prompt);
	if (!shell->input)
		return (1);
	if (shell->input && *shell->input != 0)
	{
		add_history(shell->input);
		if (!parsing(shell))
		{
			if (!init_process(shell))
			{
				if (shell->cmd_nbr > 1 || (shell->cmd_nbr == 1
						&& !is_builtin(shell->cmdlist->cmd_arg[0])))
					g_data.exit_code = pipex(shell);
				else
					g_data.exit_code = one_cmd(shell);
			}
		}
		final_free_cmd(shell);
	}
	reinit_struct(shell);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_var	*shell;

	g_data.exit_code = 0;
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
			break ;
	}
	exit_minishell(shell, g_data.exit_code);
	return (0);
}
