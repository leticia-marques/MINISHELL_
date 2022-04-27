/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:55:44 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/24 00:07:23 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	check_syntax_error(t_node **cmd)
{
	t_node	*aux;
	char	*tmp;
	char	*str;

	aux = (*cmd)->first_arg;
	if (ft_strcmp(aux->val.str, "echo") == 0)
		return (1);
	tmp = "";
	while (aux)
	{
		str = aux->val.str;
		if (aux->next != NULL)
			tmp = aux->next->val.str;
		if (ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0 || ft_strcmp(str, "<") == 0 || ft_strcmp(str, "<<") == 0 || str[0] == '\0')
		{
			if ((ft_strcmp(tmp, ">") == 0 || ft_strcmp(tmp, ">>") == 0 \
			|| ft_strcmp(tmp, "<") == 0 || ft_strcmp(tmp, "<<") == 0) || tmp[0] == '\0')
			{
				redirect_error(tmp);
				return (0);
			}
		}
		aux = aux->next;
		tmp= "";
	}
	return (1);
}
