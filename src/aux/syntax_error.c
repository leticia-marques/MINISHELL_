/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:55:44 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/29 21:22:45 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static int	check_syntax_loop(t_node *aux, char *tmp)
{
	char	*str;

	while (aux)
	{
		str = aux->val;
		if (aux->next != NULL)
			tmp = aux->next->val;
		if (ft_strcmp(str, ">") == 0 || ft_strcmp(str, ">>") == 0 || \
			ft_strcmp(str, "<") == 0 || \
			ft_strcmp(str, "<<") == 0 || str[0] == '\0')
		{
			if ((ft_strcmp(tmp, ">") == 0 || ft_strcmp(tmp, ">>") == 0 \
				|| ft_strcmp(tmp, "<") == 0 || ft_strcmp(tmp, "<<") == 0) \
				|| tmp[0] == '\0')
			{
				redirect_error(tmp);
				return (0);
			}
		}
		aux = aux->next;
		tmp = "";
	}
	return (1);
}

int	check_syntax_error(t_node **cmd)
{
	t_node	*aux;
	char	*tmp;
	int		i;

	aux = (*cmd)->first_arg;
	if (ft_strcmp(aux->val, "echo") == 0)
		return (1);
	tmp = "";
	i = check_syntax_loop(aux, tmp);
	return (i);
}
