/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:12:08 by fl-hote            #+#    #+#             */
/*   Updated: 2022/12/07 08:24:10 by fl-hote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

 // a effacer 
 // notre envp est defini à l'initialisation et risque donc de ne pas être à jour lors de l'appel à pwd
 // d'où la nouvelle version (en bas) qui fait appel à getcwd() (cwd = current working directory)
/*int	exec_pwd(char **envp) 

{
	int		x;

	x = 0;
	while (envp[x])
	{
		if (envp[x][0] == 'P' && envp[x][1] == 'W'
			&& envp[x][2] == 'D' && envp[x][3] == '=')
			{
				printf("%s\n", &envp[x][4]);
				return (0);
			}
		x++;
	}
	return (error_manager(9), ft_putendl_fd("PWD path not found", 2, 1));
}

int	exec_pwd() // A refaire avec t_env *env
{
	char *tmp;

	tmp = getcwd(NULL, 0);
	if (!tmp)
		return (error_manager(9), ft_putendl_fd("PWD path not found", 2, 1));
	printf("%s", tmp);
	free(tmp);
	return (0);
}
*/

int	exec_pwd(t_env *env)
{
	t_env *ptr;		//Fred 11/01: peut-on s'affranchir de ptr et utiliser directement env ?

	ptr = env;
	while (env)
	{
		if (!ft_strcmp(env->name, "PWD"))
		{
			printf("%s\n", env->value);
			env = ptr;
			return (0);
		}
		env = env->next;
	}
	env = ptr;
	return (1);
}