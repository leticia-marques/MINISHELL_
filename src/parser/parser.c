/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:14:49 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/28 05:28:35 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static	char	*parser_loop(t_input *src, t_token_holder *holder, \
	t_token *end_token)
{
	while (token != end_token)
	{
		if (token->text[0] == '\n')
		{
			free_token(token);
			break ;
		}
		word = new_node(name);
		if (!word)
		{
			free_node(cmd);
			free_token(token);
			return (NULL);
		}
		set_value_str(word, token->text);
		add_argument_node(cmd, word);
		free_token(token);
		token = tokenizer(src, holder, end_token);
	}
}

t_node	*parser_command(t_input *src, t_token_holder *holder)
{
	t_node	*cmd;
	t_node	*word;
	t_token	end_token;
	t_token	*token;

	cmd = new_node(command);
	if (!cmd)
		return (NULL);
	init_end_token(&end_token);
	token = tokenizer(src, holder, &end_token);
	parser_loop(src, holder, &end_token);
	return (cmd);
}
