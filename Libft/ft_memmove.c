/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 10:01:24 by lemarque          #+#    #+#             */
/*   Updated: 2021/08/27 10:01:25 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
void	*ft_memmove(void *str1, const void *str2, size_t c)
{
	size_t	i;

	i = 0;
	if (!str1 && !str2)
		return (0);
	if (str1 < str2)
	{
		ft_memcpy(str1, str2, c);
	}
	else
	{
		i = c - 1;
		while ((int)i >= 0)
		{
			((char *)str1)[i] = ((char *)str2)[i];
			i--;
		}
	}
	return (str1);
}
