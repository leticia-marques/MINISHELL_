/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinacio- < jinacio-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 16:01:13 by lemarque          #+#    #+#             */
/*   Updated: 2022/05/03 22:12:54 by jinacio-         ###   ########.fr       */
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
