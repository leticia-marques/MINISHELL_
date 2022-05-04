/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 01:24:34 by lemarque          #+#    #+#             */
/*   Updated: 2022/05/04 15:07:10 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	filter_filter(t_node **cmd)
{
	t_node		*aux;
	t_filter	filter;
	t_node		*tmp;

	aux = (*cmd)->first_arg;
	filter.line = "";
	while (aux)
	{
		if (ft_strcmp(aux->val, "<<") == 0)
		{
			filter.aux = aux->next;
			tmp = aux->prev;
			free(aux);
			tmp->next = filter.aux->next;
			free(filter.aux);
			aux = tmp;
		}
		aux = aux->next;
	}
	return (1);
}

void	filter_cmd(t_node **cmd)
{
	t_filter	filter;
	int			i;

	i = -1;
	filter.aux = (*cmd)->first_arg;
	filter.line = "";
	while (++i < 2)
		filter.aux = filter.aux->next;
	while (filter.aux != NULL)
	{
		filter.tmp_line = filter.aux->val;
		filter.tmp_line = ft_strjoin(filter.tmp_line, " ");
		filter.line = ft_strjoin(filter.line, filter.tmp_line);
		free(filter.tmp_line);
		filter.aux = filter.aux->next;
	}
	init_src(&filter.src, filter.line);
	init_holder(&filter.holder);
	filter.aux = (*cmd);
	free_node(&filter.aux);
	*cmd = parser_command(&filter.src, &filter.holder);
}
