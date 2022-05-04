/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinacio- < jinacio-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 20:05:26 by lemarque          #+#    #+#             */
/*   Updated: 2022/05/03 22:13:40 by jinacio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_strcmp(char *str, char *str2)
{
	while (*str && *str2 && *str == *str2)
	{
		str++;
		str2++;
	}
	return (*(unsigned char *)str - *(unsigned char *)str2);
}
