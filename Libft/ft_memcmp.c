/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 10:21:05 by lemarque          #+#    #+#             */
/*   Updated: 2021/08/27 10:21:06 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	if (!str1 && !str2)
		return (0);
	while (n--)
	{
		if (*(char *)str1 != *(char *)str2)
		{
			return (*(unsigned char *)str1 - *(unsigned char *)str2);
		}
		str1++;
		str2++;
	}
	return (0);
}
