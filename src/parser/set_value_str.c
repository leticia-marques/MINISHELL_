/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_value_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 01:36:05 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/29 21:23:17 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	set_value_str(t_node *node, char *val)
{
	char	*val_cpy;

	if (!val)
		node->val = NULL;
	else
	{
		val_cpy = malloc(ft_strlen(val) + 1);
		if (!val_cpy)
			node->val = NULL;
		else
		{
			ft_strlcpy(val_cpy, val, ft_strlen(val) + 1);
			node->val = val_cpy;
		}
	}
}
