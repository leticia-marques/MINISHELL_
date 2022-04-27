/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 11:39:59 by lemarque          #+#    #+#             */
/*   Updated: 2021/08/31 19:04:11 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	leng;
	size_t	new_size;

	leng = 0;
	new_size = size - 1;
	if (size)
	{
		while (*src && new_size--)
		{
			*dest = *(unsigned char *)src;
			dest++;
			src++;
			leng++;
		}
		*dest = '\0';
	}
	while (*src)
	{
		leng++;
		src++;
	}
	return (leng);
}
