/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 15:32:17 by lemarque          #+#    #+#             */
/*   Updated: 2021/09/08 21:09:18 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new_str;
	unsigned int	n;

	n = 0;
	if (!s)
		return (0);
	new_str = ft_strdup(s);
	if (!new_str)
		return (0);
	while (new_str[n])
	{
		new_str[n] = f(n, new_str[n]);
		n++;
	}
	return (new_str);
}
