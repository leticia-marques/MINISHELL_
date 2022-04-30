/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 00:05:55 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/29 22:36:33 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*stop_parser(t_token *end_token)
{
	return (end_token);
}

static void	get_quotes(t_token_holder *holder, t_input *src, \
	char *c, char symbol)
{
	while (*c != -1 && *c != '\0')
	{
		if (*c == symbol)
		{
			*c = next_char(src);
			if (*c != -1)
				fill_buffer(*c, holder);
			while (*c != symbol && *c != '\0')
			{
				*c = next_char(src);
				if (*c != -1 && *c != symbol)
					fill_buffer(*c, holder);
			}
			return ;
		}
	}
}

static void	lexer_loop(t_token_holder *holder, t_input *src, char *c)
{
	while (*c != -1)
	{
		if (*c == '\t' || *c == ' ')
		{
			if (holder->buf_position > 0)
				break ;
		}
		else if (*c == '\'' || *c == '\"')
			get_quotes(holder, src, c, *c);
		else if (*c == '\n')
		{
			if (holder->buf_position > 0)
				go_back_a_char(src);
			else
				fill_buffer(*c, holder);
			break ;
		}
		else if (*c == '|')
			break ;
		else
		{
			fill_buffer(*c, holder);
		}
		if (*c != ' ')
			*c = next_char(src);
	}
}

static void	lexer_scanner(t_token_holder *holder, t_input *src, \
t_token *end_token)
{
	char	c;

	c = next_char(src);
	if (c == '|')
		stop_parser(end_token);
	if (c == 0 || c == -1)
		return ;
	lexer_loop(holder, src, &c);
}

t_token	*tokenizer(t_input *src, t_token_holder *holder, t_token *end_token)
{
	t_token	*token;

	if (!src || !src->line_size || !src->line)
		return (end_token);
	if (!holder->token_buf)
		return (end_token);
	holder->buf_position = 0;
	holder->token_buf[0] = '\0';
	lexer_scanner(holder, src, end_token);
	if (holder->buf_position == 0)
		return (end_token);
	if (holder->buf_position >= holder->buf_size)
		holder->buf_position--;
	holder->token_buf[holder->buf_position] = '\0';
	token = create_token(holder->token_buf);
	token->src = src;
	return (token);
}
