/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 10:05:22 by lemarque          #+#    #+#             */
/*   Updated: 2021/09/03 22:02:21 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
void	*ft_memchr(const void *str, int c, size_t n)
{
	while (n--)
	{
		if (*(char *)str == (char)c)
		{
			return ((char *)str);
		}
		str++;
	}
	return (NULL);
}
