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

static void	print_cmdlist(t_cmdlist *ptr)
{
	int		i;

	while (ptr)
	{
		printf("'%s'\n", ptr->brut);
		printf("i:%s o:%s hd:%s app:%d\n", ptr->redir_input, ptr->redir_output, ptr->delim_hdoc, ptr->flag_append);
		i=-1;
		while (ptr->cmd_arg[++i])
		{
			printf("[%s]", ptr->cmd_arg[i]);
		}
		printf("\n");
		ptr = ptr->next;
	}
}
static void	main_loop(t_var *shell, char *prompt, int aff_or_exec)
{
	shell->input = readline(prompt);
	if (shell->input && *shell->input != 0)
	{
		add_history(shell->input);
		if (!parsing(shell))
		{
			if (aff_or_exec == '1') //
				print_cmdlist(shell->cmdlist); //
			else //
			{ //
				if (!init_process(shell))
				{
					if (shell->cmd_nbr > 1 || (shell->cmd_nbr == 1 && !is_builtin(shell->cmdlist->cmd_arg[0])))
						g_exit_code = pipex(shell);
					else
						g_exit_code = one_cmd(shell);
				}
			} //
		}
		free_cmdlist(&(shell->cmdlist));
		reinit_struct(shell);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_var	*shell;
	char	*prompt;

	g_exit_code = 0;
	if (argc != 2) // 1 pour affich liste only, 2 pour exec 
		return (error_manager(1));
	shell = init_struct(envp);
	if (!shell)
		return (error_manager(13));
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	while (1)
	{
		main_loop(shell, prompt, *argv[1]);
	}
	exit_minishell(shell, g_exit_code);
	return (0);
}
