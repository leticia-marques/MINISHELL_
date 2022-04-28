/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_value_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 01:36:05 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/28 05:29:11 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	set_value_str(t_node *node, char *val)
{
	char	*val_cpy;

	node->val_type = VAL_STR;
	if (!val)
		node->val.str = NULL;
	else
	{
		val_cpy = malloc(ft_strlen(val) + 1);
		if (!val_cpy)
			node->val.str = NULL;
		else
		{
			ft_strlcpy(val_cpy, val, ft_strlen(val) + 1);
			node->val.str = val_cpy;
		}
	}
}
