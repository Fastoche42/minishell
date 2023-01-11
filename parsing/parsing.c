/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:28:29 by fl-hote           #+#    #+#             */
/*   Updated: 2023/01/11 02:47:36 by marvin           ###   ########.fr       */
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

void	fill_cndlist(t_cmdlist cmdlist, int type, int start, int i)
{
	cmdlist.cmd_path = ft_substr()
}

void	ms_parse_quotes(t_var *shell)
{
	t_cmdlist	*ptr; //pointeur de parcours
	int	start;
	int	i;
	int	status; //are we inside "" (1,ascii34), inside '' (2,ascii39), or not (0)

	printf("len: %zu\n", ft_strlen(shell->input));
	start = 0;
	i = 0;
	status = 0;
	while (shell->input[i])
	{
		if (!status && (shell->input[i] == 34 || shell->input[i] == 39))
		{
			fill_cmdlist(shell->cmdlist, status, start, i);
			status = 1;
		}
		i++;
	}
}

int	ms_parsing(t_var *shell)
{
	t_cmdlist	*ptr; //pointeur de parcours

	shell->cmdlist = new_cmdlist();
	if (!shell->cmdlist)
		return (0);
	
	// trim start and end spaces
	shell->input = ft_strtrim(shell->input, " 	"); // space & tab
	printf("trim: %s\n", shell->input);

	// parse " and '
	ms_parse_quotes(shell);

	// temporaire commamde line : (ls -a | wc -l) ; (exit) ; ...
	ptr = shell->cmdlist;
	ptr->cmd_path = "/bin/ls";
	ptr->cmd_arg = ft_split("ls -l", ' ');
	ptr->cmd_env = NULL;
	ptr->redir_input = NULL;
	ptr->delim_hdoc = NULL;
	ptr->redir_output = NULL;
	ptr->flag_append = 0;

	ptr->next = new_cmdlist();
	ptr = ptr->next;
	ptr->cmd_path = "/usr/bin/head";
	ptr->cmd_arg = ft_split("head -3", ' ');
	ptr->cmd_env = NULL;
	ptr->redir_input = NULL;
	ptr->delim_hdoc = NULL;
	ptr->redir_output = NULL;
	ptr->flag_append = 0;

	ptr->next = new_cmdlist();
	ptr = ptr->next;
	ptr->cmd_path = "/bin/cat";
	ptr->cmd_arg = ft_split("cat -e", ' ');
	ptr->cmd_env = NULL;
	ptr->redir_input = NULL;
	ptr->delim_hdoc = NULL;
	ptr->redir_output = "outfile.txt";
	ptr->flag_append = 1;
	return (1);
}
