/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:07:03 by fl-hote            #+#    #+#             */
/*   Updated: 2022/12/11 18:24:42 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include "../Libft/libft.h"
# include "parsing.h"

//----------------global variable----------------//
extern int	g_exit_code;

//----------------struct----------------//
typedef struct s_env {
	char			*name;		// gauche du =
	char			*value;		// droite du =
	int				exists;		// pas deleted
	int				exported;	// exportee ou non
	struct s_env	*next;
	
}	t_env;

typedef struct s_var {
	char		*input;

	t_cmdlist	*cmdlist;		// ptr vers liste de commande => exec Morgan

	int			heredoc; // heredoc flag, à incrémenter pour chaque heredoc
	int			child; // index
	int			*pipe;
	int			*pids; // process IDs (nécessaire au forking)
	int			cmd_nbr;
	t_env		*env;

}	t_var;

//----------------minishell----------------//
t_var	*init_struct(char **envp);
t_env	*init_env(char **envp);
int		init_process(t_var *shell);
void	free_mem(t_var *shell);

//---------------parsing------------------//
//void	fill_cndlist(cmdlist, type);
void	ms_parse_quotes(t_var *shell);
int		ms_parsing(t_var *shell);

//----------------exec----------------//
int		which_command(t_var *shell, t_cmdlist *cmd); // mise à jour 10/01/2023
void	handler_sig(int signum);
int		ms_execute(t_var *shell);
int		exec_pwd(t_env *env); // mise à jour 05/01/2023
int		exec_env(t_env *env); // mise à jour 10/01/2023
int		exec_echo(t_cmdlist *cmd); // mise à jour 05/01/2023
int		exec_exit(t_var *shell); // je ne crois pas quelle soit nécessaire
int		exec_cd(t_cmdlist *cmd, t_env *env); // mise à jour 10/01/2023
int		exec_export(t_cmdlist *cmd, t_env *env); // mise à jour 10/01/2023
int		exec_unset(t_cmdlist *cmd, t_env *env); // mise à jour 10/01/2023
void	redirection(t_var *shell, t_cmdlist *ptr); // toujours nécessaire ?
int		number_of_cmd(t_var *shell);

int  	pipex(t_var *shell);
char 	*get_cmd(char *cmd, t_var *shell);
int		file_handler(t_cmdlist *cmd);
int		redir_first_last(t_var *shell, t_cmdlist *cmd);
int		redir_other(t_var *shell, t_cmdlist *cmd);

//----------------check_error----------------//
int		error_manager(int error);

//----------------utils----------------//
int		count_args(t_var *shell);
void	find_cmd(t_var *shell, char **var);
int		nb_var_in_env(char **env);
char	*modif_input(char *input);
int		ft_free_splited(char **str);
void	close_fds(t_var *shell);
void	free_strs(char *str, char **strs);
char	**build_envp(t_env *env);
int		ft_unlink_heredocs(t_var *shell);

#endif
