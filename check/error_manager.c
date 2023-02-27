/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: event <event@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 10:53:13 by fl-hote           #+#    #+#             */
/*   Updated: 2023/02/27 12:46:26 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	error_manager2(int error)
{
	if (error == 13)
		return (perror("Malloc error"), (int)errno);
	else if (error == 20)
		return (ft_putendl_fd("Quotes not properly closed", 2, 1));
	else if (error == 21)
		return (ft_putendl_fd("Error in redirection file or delimitor", 2, 1));
	return (ft_putendl_fd("Undefined error", 2, 1));
}

int	error_manager(int error)
{
	if (error == 1)
		return (ft_putendl_fd("Invalid number of arguments", 2, 1));
	else if (error == 2)
		return (perror("Invalid command"), (int)errno);
	else if (error == 3)
		return (perror("Invalid builtin"), (int)errno);
	else if (error == 4)
		return (perror("Invalid export"), (int)errno);
	else if (error == 5)
		return (perror("PID error"), (int)errno);
	else if (error == 6)
		return (perror("Pipe error"), (int)errno);
	else if (error == 7)
		return (perror("Fork error"), (int)errno);
	else if (error == 8)
		return (perror("Not enough arguments"), (int)errno);
	else if (error == 9)
		return (perror("Built-in error"), (int)errno);
	else if (error == 10)
		return (perror("Unexpected error"), (int)errno);
	else if (error == 11)
		return (perror("Redirection error"), (int)errno);
	else if (error == 12)
		return (perror("File handler error"), (int)errno);
	return (error_manager2(error));
}
