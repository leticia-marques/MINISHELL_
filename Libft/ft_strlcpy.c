/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinacio- < jinacio-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 11:39:59 by lemarque          #+#    #+#             */
/*   Updated: 2022/05/03 22:13:10 by jinacio-         ###   ########.fr       */
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
