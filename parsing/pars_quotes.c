/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:04:58 by event             #+#    #+#             */
/*   Updated: 2023/02/27 15:02:29 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	dollar_found(char **str, char **end, char **start, t_env *env)
{
	char	*str2;

	ft_concat(str, ft_strndup (*start, (*end - *start)));
	(*end)++;
	if (**end == '?')
		str2 = ft_itoa(g_exit_code);
	else
		str2 = replace_by_var(end, env);
	ft_concat(str, str2);
	*start = *end + 1;
}

static void	save_before_dq(char **str, char **start, char **end, int *in_dq)
{
	ft_concat(str, ft_strndup (*start, (*end - *start)));
	*start = *end + 1;
	*in_dq = 1 - *in_dq;
}

void	quotes_and_var(char **str, t_env *env, int in_dq)
{
	char	*start;
	char	*end;
	char	*str2;

	start = *str;
	end = start;
	*str = NULL;
	while (*end)
	{
		if (*end == '\'' && !in_dq)
		{
			ft_concat(str, ft_strndup (start, (end - start)));
			end++;
			str2 = what_inside_sq(&end);
			ft_concat(str, str2);
			start = end + 1;
		}
		else if (*end == '"')
			save_before_dq(str, &start, &end, &in_dq);
		else if (*end == '$' && ft_iscarvar(*(end + 1)))
			dollar_found(str, &end, &start, env);
		end++;
	}
	ft_concat(str, ft_strndup (start, (end - start)));
}
