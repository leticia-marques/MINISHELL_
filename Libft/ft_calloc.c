/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 11:03:11 by lemarque          #+#    #+#             */
/*   Updated: 2021/08/26 11:03:12 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = malloc(n * size);
	if (!p)
		return (0);
	while (i < n * size)
	{
		p[i++] = 0;
	}
	return ((void *)p);
}
