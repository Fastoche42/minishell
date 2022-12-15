<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 10:53:13 by mfusil            #+#    #+#             */
/*   Updated: 2022/12/08 14:29:23 by mfusil           ###   ########.fr       */
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
		return (ft_putendl_fd("Pipe error", 2, 1));
	else if (error == 6)
		return (ft_putendl_fd("Fork error", 2, 1));
	else if (error == 7)
		return (ft_putendl_fd("Noy enough arguments", 2, 1));
	return (0);
}
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfusil <mfusil@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 10:53:13 by mfusil            #+#    #+#             */
/*   Updated: 2022/12/08 14:29:23 by mfusil           ###   ########.fr       */
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
	return (0);
}
>>>>>>> main
