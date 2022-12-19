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

/* A disparaitre
char	**init_env(char **envp)
{
	char	**var;
	int		i;

	i = 0;
	var = malloc (sizeof(char *) * ft_nb_lines_tab(envp));
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		var[i] = ft_strdup(envp[i]);
		i++;
	}
	return (var);
}
*/

int	main(int argc, char **argv, char **envp)
{
	t_var	*shell;

	(void)argv;
	if (argc != 1)
		return (error_manager(1));
	shell = init_struct(envp);
	if (!shell)
		return (1);
	//envir = init_env(envp);			// A disparaitre
	signal(SIGINT, handler_sig);
	signal(SIGQUIT, handler_sig);
	while (1)
	{
		shell->input = readline("minishell> ");
		if (shell->input && ((int)shell->input != 13))
		{
			add_history(shell->input); // y compris que des spaces
			if (!ft_strcmp(shell->input, "exit"))     //Temporaire, ou pas....
			{
				ft_putendl_fd("exit", 1, 0);
				break ;
			}
			if (ms_parsing(shell)) //creer lst-ch et return 1 si ok
				if (!init_process(shell))
					ms_execute(shell);
			free(shell->input);
		}
	}
	free_mem(shell);
	return (0);
}

/*
 * fonction free mem qui permettra de free chaque ligne du tableau
 */
