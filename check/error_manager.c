/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 10:53:13 by fl-hote            #+#    #+#             */
/*   Updated: 2022/12/08 14:29:23 by fl-hote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	error_manager(int error)
{
	if (error == 1)
		return (ft_putendl_fd("Invalid number of arguments", 2, 1));
	else if (error == 2)
		return (ft_putendl_fd("Invalid command", 2, 1));
	else if (error == 3)
		return (ft_putendl_fd("Invalid builtin", 2, 1));
	else if (error == 4)
		return (ft_putendl_fd("Invalid export", 2, 1));
	else if (error == 5)
		return (ft_putendl_fd("PID error", 2, 1));
	else if (error == 6)
		return (ft_putendl_fd("Pipe error", 2, 1));
	else if (error == 7)
		return (ft_putendl_fd("Fork error", 2, 1));
	else if (error == 8)
		return (ft_putendl_fd("Not enough arguments", 2, 1));
	else if (error == 9)
		return (ft_putendl_fd("Built-in error ", 2, 1));
	else if (error == 10)
		return (ft_putendl_fd("Unexpected error", 2, 1));
	else if (error == 11)
		return (ft_putendl_fd("Redirection error", 2, 1));
	else if (error == 12)
		return (ft_putendl_fd("File handler error", 2, 1));
	return (0);
}
