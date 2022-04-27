/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 23:18:33 by lemarque          #+#    #+#             */
/*   Updated: 2021/08/29 23:18:34 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	n;

	n = 0;
	if (s && f)
	{
		while (s[n])
		{
			f(n, &s[n]);
			n++;
		}
	}
}
