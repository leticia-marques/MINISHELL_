/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:14:49 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/24 19:10:50 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

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
	token =  tokenizer(src, holder, &end_token);
	while (token != &end_token)
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
		token = tokenizer(src, holder, &end_token);
	}
	return (cmd);
}
