/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 00:05:55 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/23 02:22:18 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*stop_parser(t_token *end_token)
{
	return (end_token);
}

// static void	get_quotes(t_token_holder *holder, t_input *src, char *c)
// {
// 	if (*c == '\'')
// 	{
// 		if (src->line[src->position + 1] == '\'' && src->line[src->position - 1] ==
// 		' ' && (src->line[src->position + 2] == ' ' ||
// 		src->line[src->position + 2] == '\0'))
// 		{
// 			fill_buffer(*c, holder);
// 			*c = next_char(src);
// 			fill_buffer(*c, holder);
// 			return ;
// 		}
// 		else if (src->line[src->position + 1] == '\'')
// 		{
// 			//fill_buffer(*c, holder);
// 			//*c = next_char(src);
// 			*c = next_char(src);
// 			get_quotes(holder, src, c);
// 		}
// 		*c = next_char(src);
// 		holder->inside_quote = 0;
// 		while (*c != '\'' && *c != -1 && !holder->inside_quote)
// 		{
// 			fill_buffer(*c, holder);
// 			*c = next_char(src);
// 		}
// 		*c = next_char(src);
// 		holder->inside_quote = -1;
// 		//*c = next_char(src);
// 		get_quotes(holder, src, c);
// 	}
// 	//else if (src->line[src->position])
// 	else if (*c == '\"')
// 	{
// 		/*if (*c == '\"')
// 			*c = next_char(src);*/
// 		*c = next_char(src);

// 		while (*c != '\"' && *c != -1)
// 		{
// 			fill_buffer(*c, holder);
// 			*c = next_char(src);
// 		}
// 		/*if (*c == '\"')
// 			*c = next_char(src);*/
// 		*c = next_char(src);
// 		get_quotes(holder, src, c);
// 	}
// 	else if (*c == ' ')
// 		return ;
// 	else if (*c != -1 && *c != ' ')
// 	{
// 		fill_buffer(*c, holder);
// 		*c = next_char(src);
// 		get_quotes(holder, src, c);
// 	}
// }

static void     get_quotes(t_token_holder *holder, t_input *src, char *c, char symbol)
{
	// char	tmp;

	// tmp = symbol;
	while (*c != -1)
	{
		if (*c == symbol)
		{
			*c = next_char(src);
			if (*c != -1)
				fill_buffer(*c, holder);
			// if (src->line[src->position + 1] != )
				// get_quotes(holder, src, c, tmp);
			while (*c != symbol)
			{
				*c = next_char(src);
				if (*c != -1 && *c != symbol )
					fill_buffer(*c, holder);
			}
			*c = next_char(src);
			return ;
		}
		// else
		// {
		// 	if (*c != -1)
		// 		fill_buffer(*c, holder);
		// 	fill_buffer(*c, holder);
		// *c = next_char(src);
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
	while (c != -1)
	{
		if (c == '\t' || c == ' ')
		{
			if (holder->buf_position > 0)
				break ;
		}
		else if (c == '\'' || c == '\"')
			get_quotes(holder, src, &c, c);
		else if (c == '\n')
		{
			if (holder->buf_position > 0)
				go_back_a_char(src);
			else
				fill_buffer(c, holder);
			break ;
		}
		else if (c == '|')
			break ;
		else
		{
			fill_buffer(c, holder);
		}
		if (c != ' ')
			c = next_char(src);
	}
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
