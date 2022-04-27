/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanner_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 21:33:56 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/11 18:51:30 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static int	increase_buffer(t_token_holder *holder)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = holder->token_buf;
	holder->token_buf = ft_calloc(holder->buf_size * 2, sizeof(char));
	if (!holder->token_buf)
		return (0);
	while (i < holder->buf_size)
	{
		holder->token_buf[i] = tmp[i];
		i++;
	}
	holder->buf_size *= 2;
	free(tmp);
	return (1);
}

void	fill_buffer(char c, t_token_holder *holder)
{
	holder->token_buf[holder->buf_position++] = c;
	if (holder->buf_position >= holder->buf_size)
		increase_buffer(holder);
}

t_token	*create_token(char *str)
{
	t_token	*token;
	char	*aux;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->text_size = ft_strlen(str) + 1;
	aux = malloc(token->text_size);
	if (!aux)
	{
		free(token);
		return (NULL);
	}
	ft_strlcpy(aux, str, token->text_size);
	token->text = aux;
	return (token);
}
