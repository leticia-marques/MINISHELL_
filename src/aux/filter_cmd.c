/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 01:24:34 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/24 20:03:02 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

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
		filter.tmp_line = filter.aux->val.str;
		filter.tmp_line = ft_strjoin(filter.tmp_line, " ");
		filter.line = ft_strjoin(filter.line, filter.tmp_line);
		free(filter.tmp_line);
		filter.aux = filter.aux->next;
	}
	init_src(&filter.src, filter.line);
	init_holder(&filter.holder);
	filter.aux = (*cmd);
	free_node(filter.aux);
	*cmd = parser_command(&filter.src, &filter.holder);
}
