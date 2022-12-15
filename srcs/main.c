/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:07:56 by mfusil            #+#    #+#             */
/*   Updated: 2022/12/15 17:26:53 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ESSAI MODIF
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
		//shell = init_struct();
		shell->input = readline("minishell> ");
		if (shell->input == NULL)
			exit(0);
		if (shell->input && !ft_strcmp(shell->input, "exit"))     //Temporaire
			break ;
		add_history(shell->input);
		if (ms_parsing(shell)) //creer lst-ch et return 1 si ok;
			ms_execute(shell);
		free(shell->input);
	}
	free_mem(shell);
	return (0);
}

/*
 * fonction free mem qui permettra de free chaque ligne du tableau
 */
