/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 19:20:58 by lemarque          #+#    #+#             */
/*   Updated: 2021/08/28 09:44:31 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*new_word;

	size = ft_strlen(s);
	new_word = malloc(sizeof(char) * (size + 1));
	if (!new_word)
		return (0);
	size = 0;
	while (s[size] != '\0')
	{
		new_word[size] = s[size];
		size++;
	}
	new_word[size] = '\0';
	return (new_word);
}
