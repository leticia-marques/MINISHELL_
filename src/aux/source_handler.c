/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 18:18:03 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/05/06 00:09:18 by lemarque         ###   ########.fr       */
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
	// char	pos;

	// pos = 0;
	if (src->position == -2)
		src->position = -1;
	// else
	// 	pos = src->line[src->position];
	// (void)pos;
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
