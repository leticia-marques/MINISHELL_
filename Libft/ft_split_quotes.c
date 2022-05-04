/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinacio- < jinacio-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 22:10:37 by jinacio-          #+#    #+#             */
/*   Updated: 2022/05/03 22:11:39 by jinacio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	word_count(char const *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		while ((*str == c || *str == '\"' || *str == '\'') && *str)
			str++;
		if (*str != c && *str)
			count++;
		while (*str != c && *str)
			str++;
	}
	return (count);
}

static int	word_size_count(char const *str, char c)
{
	int	size;

	size = 0;
	while (*str != c && *str)
	{
		if (*str == '\'' || *str == '\"')
			break ;
		if (*str != c && *str != '\'' && *str != '\"' && *str)
			size++;
		str++;
	}
	return (size);
}

char	**ft_split_quotes(char const *str, char c)
{
	char	**splits ;
	int		i;

	i = 0;
	splits = malloc(word_count(str, c) * sizeof(char *) + 1);
	if (splits)
		return (NULL);
	while (*str)
	{
		if (*str != c && *str != '\'' && *str != '\"')
		{
			splits[i] = ft_substr(str, 0, word_size_count(str, c));
			if (!splits[i])
				return (NULL);
			str += word_size_count(str, c);
			i++;
		}
		while ((*str == c || *str == '\'' || *str == '\"') && *str)
			str++;
	}
	splits[i++] = NULL;
	return (splits);
}
