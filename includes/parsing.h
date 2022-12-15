/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 17:16:05 by mfusil            #+#    #+#             */
/*   Updated: 2022/12/11 12:33:42 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_cmdlist
{
	char				*cmd_path;
	char				**cmd_arg;
	char				**cmd_env;
	char				*redir_input;
	char				*redir_output;
	char				*redir_append;
	char				*redir_hdoc;
	struct s_cmdlist	*next;
}					t_cmdlist;

#endif