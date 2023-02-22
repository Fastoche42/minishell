/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 11:32:51 by marvin            #+#    #+#             */
/*   Updated: 2023/02/22 18:58:52 by event            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void*	ft_realloc(void* ptr, size_t size)
{
	void*	new_ptr;

	if (!ptr)
		return (malloc(size));
	else if (size == 0)
	{
		free(ptr);
		return NULL;
	}
	else
	{
		new_ptr = malloc(size);
		if (new_ptr == NULL)
			return NULL;
		ft_memcpy(new_ptr, ptr, size);
		if (ptr)
			free(ptr);
		ptr = NULL;
		return new_ptr;
	}
}
