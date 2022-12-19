/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fl-hote <fl-hote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:50:19 by fl-hote            #+#    #+#             */
/*   Updated: 2022/05/30 15:09:27 by fl-hote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (*lst && *del)
	{
		while (*lst)
		{
			tmp = *lst;
			ft_lstdelone(*lst, *del);
			*lst = tmp->next;
		}
	}
}
