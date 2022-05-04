/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinacio- < jinacio-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:14:49 by lemarque          #+#    #+#             */
/*   Updated: 2022/05/03 19:01:20 by jinacio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static void	parser_command_aux(t_parser parser)
{
	set_value_str(parser.word, parser.token->text);
	add_argument_node(parser.cmd, parser.word);
	free_token(parser.token);
}

t_node	*parser_command(t_input *src, t_token_holder *holder)
{
	t_parser	parser;

	parser.cmd = new_node();
	if (!parser.cmd)
		return (NULL);
	init_end_token(&parser.end_token);
	parser.token = tokenizer(src, holder, &parser.end_token);
	while (parser.token != &parser.end_token)
	{
		if (parser.token->text[0] == '\n')
		{
			free_token(parser.token);
			break ;
		}
		parser.word = new_node();
		if (!parser.word)
		{
			free_node(&parser.cmd);
			free_token(parser.token);
			return (NULL);
		}
		parser_command_aux(parser);
		parser.token = tokenizer(src, holder, &parser.end_token);
	}
	return (parser.cmd);
}
