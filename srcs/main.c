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
			printf("[%s]  ", ptr->cmd_arg[i]);
		}
		printf("\n");
		ptr = ptr->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_var	*shell;

	g_exit_code = 0;
	(void)argv;
	if (argc != 1)
		return (error_manager(1));
	shell = init_struct(envp);
	if (!shell)
		return (1);
	signal(SIGINT, handler_sig);
	signal(SIGQUIT, handler_sig);
	while (1)
	{
		shell->input = readline("minishell> ");
		if (shell->input && (shell->input != 0))
		{
			add_history(shell->input);					// y compris que des spaces
			if (!ft_strcmp(shell->input, "exit"))		//Temporaire, ou pas....
			{
				ft_putendl_fd("exit", 1, 0);
				break ;
			}
			if (!parsing(shell))
				print_cmdlist(shell->cmdlist);
				//temporaire test parsing only
				//if (!init_process(shell))
					//g_exit_code = pipex(shell);
			free_cmdlist(&(shell->cmdlist));
			reinit_struct(shell);
		}
	}
	exit_minishell(shell, g_exit_code);
	return (0);
}
