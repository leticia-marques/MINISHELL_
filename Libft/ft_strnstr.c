/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 16:01:13 by lemarque          #+#    #+#             */
/*   Updated: 2021/09/07 23:36:55 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	leng;

	leng = ft_strlen(little);
	if (little[0] == '\0')
		return ((char *)big);
	while (*big && leng <= len--)
	{
		if (ft_strncmp(big, little, leng) == 0)
			return ((char *)big);
		big++;
	}
	return (NULL);
}
