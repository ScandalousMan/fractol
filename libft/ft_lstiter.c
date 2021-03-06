/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguemy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 14:01:12 by aguemy            #+#    #+#             */
/*   Updated: 2016/11/25 16:30:22 by aguemy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	if (lst != NULL && f)
	{
		while (lst->next != NULL)
		{
			f(lst);
			lst = lst->next;
		}
		f(lst);
	}
}
