/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 08:59:01 by lemarque          #+#    #+#             */
/*   Updated: 2021/09/07 18:06:26 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = n;
	if (!dest && !src)
		return (0);
	while (n--)
	{
		*(char *)dest = *(char *)src;
		dest++;
		src++;
	}
	return (dest - i);
}
