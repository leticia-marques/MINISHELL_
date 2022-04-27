/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 01:08:24 by lemarque          #+#    #+#             */
/*   Updated: 2021/09/07 18:20:39 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	if (n == 0)
		return (0);
	while ((*str1 || *str2) && (*str1 == *str2) && n--)
	{
		str1++;
		str2++;
	}
	if (n)
		return ((*(unsigned char *)str1 - *(unsigned char *)str2));
	return (0);
}
