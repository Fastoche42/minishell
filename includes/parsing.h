/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:04:36 by fl-hote           #+#    #+#             */
/*   Updated: 2023/01/26 15:22:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#define MAX_LINE_LENGTH 256

typedef struct s_cmdlist
{
	char				*cmd_path;
	char				**cmd_arg;
	char				**cmd_env; // à supprimer
	int					type;
	char				*redir_input;	//filename or NULL
	char				*delim_hdoc;	//exit word or NULL
	char				*redir_output;	//filename
	int					flag_append;	//flag
	int					fd_in;
	int					fd_out;
	struct s_cmdlist	*next;
}					t_cmdlist;

#endif