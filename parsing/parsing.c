/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:28:29 by fl-hote           #+#    #+#             */
/*   Updated: 2023/02/10 00:14:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	free_cmdlist(t_cmdlist **head)
{
	t_cmdlist	*ptr;

	while (*head)
	{
		ptr = *head;
		free(ptr->brut);
		//free_strs(NULL, ptr->cmd_arg);
		//free(ptr->cmd_path);
		free(ptr->redir_input);
		free(ptr->redir_output);
		*head = (*head)->next;
		ptr->next = NULL;
		free(ptr);
	}
	head = NULL;
	return (0);
}

static t_cmdlist	*new_cmdnode(void)
{
	t_cmdlist	*node;

	node = malloc(sizeof(t_cmdlist));
	if (!node)
		return (NULL);
	node->brut = NULL;
	node->cmd_path = NULL;
	node->redir_input = NULL;
	node->delim_hdoc = NULL;
	node->redir_output = NULL;
	node->flag_append = 0;
	node->fd_in = 0;
	node->fd_out = 1;
	node->next = NULL;
	return (node);
}

static void parse_pipes(t_var *shell)
{
	int in_single_quotes;
	int in_double_quotes;
	const char *start;
	const char *end;
	t_cmdlist *current;
	char *token;
	int length;
	int	nbn = 0;

	in_single_quotes = 0;
	in_double_quotes = 0;
	start = shell->input;
	end = shell->input;
	while (*end)
	{
		if (*end == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (*end == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		else if (*end == '|' && !in_single_quotes && !in_double_quotes)
		{
			length = end - start;
			token = malloc(length + 1);
			memcpy(token, start, length);
			token[length] = '\0';
			//printf ("token: %s\n", token);
			if (!shell->cmdlist)
			{
				shell->cmdlist = new_cmdnode();
				current = shell->cmdlist;
			}
			else
			{
				current->next = new_cmdnode();
				current = current->next;
			}
			current->brut = token;
			nbn++;

			start = end + 1;
		}
		end++;
	}

	length = end - start;
	token = malloc(length + 1);
	memcpy(token, start, length);
	token[length] = '\0';
	//printf ("token: %s\n", token);
	if (!shell->cmdlist)
	{
		shell->cmdlist = new_cmdnode();
		current = shell->cmdlist;
	}
	else
	{
		current->next = new_cmdnode();
		current = current->next;
	}
	current->brut = token;
	nbn++;
	printf("nb noeuds: %d\n", nbn);
}

int	parsing(t_var *shell)
{
//	t_cmdlist	*ptr; //pointeur de parcours

	// parse "|" avoiding quotes + fill cmdlist
	parse_pipes(shell);

	// temporaire commamde line : (ls -a | wc -l) ; (exit) ; ...
 /*
	shell->cmdlist = new_cmdnode();
	if (!shell->cmdlist)
		return (0);

	ptr = shell->cmdlist;
	ptr->cmd_path = "/bin/ls";
	ptr->cmd_arg = ft_split("ls -l", ' ');

	ptr->next = new_cmdnode();
	ptr = ptr->next;
	ptr->cmd_path = "/usr/bin/head";
	ptr->cmd_arg = ft_split("head -3", ' ');

	ptr->next = new_cmdnode();
	ptr = ptr->next;
	ptr->cmd_path = "/bin/cat";
	ptr->cmd_arg = ft_split("cat -e", ' ');
*/
	return (1);
}
