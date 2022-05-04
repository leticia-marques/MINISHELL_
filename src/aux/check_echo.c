/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 20:14:19 by lemarque          #+#    #+#             */
/*   Updated: 2022/05/04 16:59:29 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	check_echo(t_node **cmd)
{
	t_node	*aux;
	int		i;

	i = 0;
	aux = (*cmd)->first_arg->next;
	while (aux)
	{
		if (ft_strcmp(aux->val, "\'") == 0 || \
			ft_strcmp(aux->val, "\"") == 0)
		{
			free(aux->val);
			aux->val = ft_strdup("");
		}
		if (ft_strcmp(aux->val, "-n") == 0)
		{
			i = 1;
			aux = aux->next;
		}
		printf("%s", aux->val);
		aux = aux->next;
	}
	if (i != 1)
		printf("\n");
	return (0);
}
