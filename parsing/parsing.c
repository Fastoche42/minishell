/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:28:29 by mfusil            #+#    #+#             */
/*   Updated: 2022/12/15 13:03:08 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmdlist	*new_cmdlist(void)
{
	t_cmdlist	*node;

	node = malloc(sizeof(t_cmdlist));
	if (!node)
		return (NULL);
	node->next = NULL;
	return (node);
}

int	ms_parsing(t_var *shell)
{
	t_cmdlist	*ptr; //pointeur de parcours

	shell->cmdlist = new_cmdlist();
	if (!shell->cmdlist)
		return (0);

	// temporaire commamde line : (ls -a | wc -l) ; (exit) ; ...
	ptr = shell->cmdlist;
	ptr->cmd_path = "/bin/ls";
	ptr->cmd_arg = ft_split("ls -l", ' ');
	ptr->cmd_env = NULL;
	ptr->redir_input = NULL;
	ptr->redir_hdoc = NULL;
	ptr->redir_output = NULL;
	ptr->redir_append = NULL;

	ptr->next = new_cmdlist();
	ptr = ptr->next;
	ptr->cmd_path = "/usr/bin/head";
	ptr->cmd_arg = ft_split("head -3", ' ');
	ptr->cmd_env = NULL;
	ptr->redir_input = NULL;
	ptr->redir_hdoc = NULL;
	ptr->redir_output = NULL;
	ptr->redir_append = NULL;

	ptr->next = new_cmdlist();
	ptr = ptr->next;
	ptr->cmd_path = "/bin/cat";
	ptr->cmd_arg = ft_split("cat -e", ' ');
	ptr->cmd_env = NULL;
	ptr->redir_input = NULL;
	ptr->redir_hdoc = NULL;
	ptr->redir_output = NULL;
	//ptr->redir_append = "outfile";
	ptr->redir_append = NULL;
	return (1);
}
