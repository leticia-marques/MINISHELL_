/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque < lemarque@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 14:56:48 by lemarque          #+#    #+#             */
/*   Updated: 2022/03/18 02:07:25 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_word;
	size_t	strings_size;
	size_t	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	strings_size = ft_strlen(s1) + ft_strlen(s2);
	new_word = malloc(sizeof(char) * strings_size + 1);
	if (new_word == NULL)
		return (0);
	while (i < strings_size)
	{
		if (i < ft_strlen(s1))
			new_word[i] = s1[i];
		else
			new_word[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	new_word[strings_size] = '\0';
	return (new_word);
}
