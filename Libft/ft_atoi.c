/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 00:37:35 by lemarque          #+#    #+#             */
/*   Updated: 2021/09/08 03:18:48 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
int	ft_atoi(const char *str)
{
	int	sign;
	int	numb;
	int	i;

	sign = 1;
	numb = 0;
	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if ((str[i] == '-' || str[i] == '+') || ft_isdigit(str[i]))
	{
		if (str[i] == '-' || str[i] == '+')
		{
			if (str[i] == '-')
				sign = -1;
			i++;
		}
		while (ft_isdigit(str[i]))
		{
			numb = (numb * 10) + (str[i] - '0');
			i++;
		}
		return (numb * sign);
	}
	return (0);
}
