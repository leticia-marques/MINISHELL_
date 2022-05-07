/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:18:03 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/05/07 04:44:40 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	go_back_a_char(t_input *src)
{
	if (src->position < 0)
		return ;
	src->position--;
}

char	next_char(t_input *src)
{
	if (src->position == -2)
		src->position = -1;
	if (++src->position >= src->line_size)
	{
		src->position = src->line_size;
		return (-1);
	}
	return (src->line[src->position]);
}

char	peek_char(t_input *src)
{
	long	pos;

	pos = src->position;
	if (pos == -2)
		pos++;
	pos++;
	if (pos >= src->line_size)
		return (-1);
	return (src->line[pos]);
}

void	skip_white_spaces(t_input *src)
{
	char	c;

	c = peek_char(src);
	while ((c != -1) && (c == ' ' || c == '\t'))
	{
		next_char(src);
		c = peek_char(src);
	}
}
