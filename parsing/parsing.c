/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:28:29 by fl-hote           #+#    #+#             */
/*   Updated: 2023/02/06 03:04:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_cmdlist	*new_cmdlist(void)
{
	t_cmdlist	*node;

	node = malloc(sizeof(t_cmdlist));
	if (!node)
		return (NULL);
	node->redir_input = NULL;
	node->delim_hdoc = NULL;
	node->redir_output = NULL;
	node->flag_append = 0;
	node->fd_in = 0;
	node->fd_out = 1;
	node->next = NULL;
	return (node);
}

//void split_string(const char *input, Node **head)
static void parse_quotes(t_var *shell)
{
	int in_single_quotes;
	int in_double_quotes;
	const char *start;
	const char *end;
	//t_cmdlist *new_node;
	char *token;
	int length;

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
			printf ("token: %s\n", token);

			shell->cmdlist = new_cmdlist();
			shell->cmdlist->cmd_path = token;
			//new_node = (Node *) malloc(sizeof(Node));
			//new_node->token = token;
			//new_node->next = *head;
			//*head = new_node;

			start = end + 1;
		}
		end++;
	}

	length = end - start;
	token = malloc(length + 1);
	memcpy(token, start, length);
	token[length] = '\0';
	printf ("token: %s\n", token);

	shell->cmdlist = new_cmdlist();
	shell->cmdlist->cmd_path = token;
	//new_node = malloc(sizeof(Node));
	//new_node->token = token;
	//new_node->next = *head;
	//*head = new_node;
}

int	parsing(t_var *shell)
{
	t_cmdlist	*ptr; //pointeur de parcours

	shell->cmdlist = new_cmdlist();
	if (!shell->cmdlist)
		return (0);
	
	shell->input = ft_strtrim(shell->input, " 	"); // space & tab
	//printf("trim: %s\n", shell->input);

	// parse "|" avoiding quotes
	parse_quotes(shell);

	// temporaire commamde line : (ls -a | wc -l) ; (exit) ; ...
	ptr = shell->cmdlist;
	ptr->cmd_path = "/bin/ls";
	ptr->cmd_arg = ft_split("ls -l", ' ');

	ptr->next = new_cmdlist();
	ptr = ptr->next;
	ptr->cmd_path = "/usr/bin/head";
	ptr->cmd_arg = ft_split("head -3", ' ');
 /*
	ptr->next = new_cmdlist();
	ptr = ptr->next;
	ptr->cmd_path = "/bin/cat";
	ptr->cmd_arg = ft_split("cat -e", ' ');
*/
	return (1);
}
