/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 20:14:19 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/22 20:21:30 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"


int	check_echo(t_node **cmd)
{
	t_node *aux;

	aux = (*cmd)->first_arg;

	while(aux)
	{
		if (ft_strcmp(aux->val.str, "\'") == 0 || \
			ft_strcmp(aux->val.str, "\"") == 0)
		{
			free(aux->val.str);
			aux->val.str = ft_strdup("");
		}
		aux = aux->next;
	}
	return (1);
}
