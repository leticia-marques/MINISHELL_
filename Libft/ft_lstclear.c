/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 00:05:02 by lemarque          #+#    #+#             */
/*   Updated: 2021/09/07 01:06:23 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*help;

	while (*lst)
	{
		help = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = help;
	}
	*lst = NULL;
}
