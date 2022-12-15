/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:47:45 by mfusil            #+#    #+#             */
/*   Updated: 2022/12/09 15:59:08 by mfusil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	redirection_heredocs(t_var *shell, t_cmdlist *ptr)
{
	char	*str;
	int		fd;

	fd = open(".heredocs", O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (fd < -1)
		return (ft_putstr_fd("error heredocs\n", 2));
	str = readline("> ");
	while (str != NULL)
	{
		str = readline("> ");
	}
}

void	redirection_infile(t_var *shell, t_cmdlist *ptr)
{
	shell->infile = open(ptr->redir_input, O_RDONLY);
	if (shell->infile < 0) //fichier pas trouvé
		return (ft_putstr_fd("error infile\n", 2));
	dup2(shell->infile, STDIN_FILENO);
}

void	redirection_outfile(t_var *shell, t_cmdlist *ptr)
{
	shell->outfile = open(ptr->redir_output, O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (shell->outfile < -1)
		return (ft_putstr_fd("error outfile\n", 2));
	dup2(shell->outfile, STDOUT_FILENO);
}

void	redirection_append(t_var *shell, t_cmdlist *ptr)
{
	shell->outfile = open(ptr->redir_output, O_WRONLY | O_APPEND | O_CREAT, 0664);
	if (shell->outfile < -1)
		return (ft_putstr_fd("error append\n", 2));
	dup2(shell->outfile, STDOUT_FILENO);	
}

void	redirection(t_var *shell, t_cmdlist *ptr)
{
	//if (cmd[i] == '>' && cmd[i + 1] == '>')
			//redirection_append(shell, ptr);
	//else if (cmd[i] == '<' && cmd[i + 1] == '<')
			//redirection_heredocs(shell);
	if (ptr->redir_input)
		redirection_infile(shell, ptr);
	if (ptr->redir_output)
		redirection_outfile(shell, ptr);
}

/**
 * J'ai pensé que dans redirection comme j'ai pas le droit de faire > et >> par exemple faire un compteur à 0 et dès qu'il rentre dans infile par exemple je le met à 1 et ce i je le met dans append et faut qu'il soit = 0 pour rentrer dedans
 *
**/
