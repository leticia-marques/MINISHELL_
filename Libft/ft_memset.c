/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 08:54:59 by lemarque          #+#    #+#             */
/*   Updated: 2021/08/27 08:55:01 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
void	*ft_memset(void *ptr, int x, size_t n)
{
	void	*prt2;

	prt2 = ptr;
	while (n--)
	{
		*(char *)ptr = x;
		ptr++;
	}
	return (prt2);
}
