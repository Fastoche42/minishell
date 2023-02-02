/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:04:36 by fl-hote           #+#    #+#             */
/*   Updated: 2023/02/01 17:35:20 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#define MAX_LINE_LENGTH 256

typedef struct s_cmdlist
{
	char				*cmd_path;
	char				**cmd_arg;
	int					type;
	char				*redir_input;	//filename or NULL
	char				*delim_hdoc;	//exit word or NULL
	char				*redir_output;	//filename or NULL
	int					flag_append;	//flag
	int					fd_in; // initialiser à 0
	int					fd_out; // initialiser à 1
	struct s_cmdlist	*next;
}					t_cmdlist;

#endif
