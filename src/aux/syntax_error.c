/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:55:44 by lemarque          #+#    #+#             */
/*   Updated: 2022/05/06 23:08:30 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static int	check_string_util(char *str, int *i, char c)
{

	if (str[*i+1] && str[*i+1] == c)
		*i+= 1;
	while (str[++*i] == ' ' && str[*i])
		;
	if (str[*i] == '<' || str[*i] == '>' || str[*i] == '\0')
	{
		redirect_error(str+*i);
		return (1);
	}
	return (0);
}

int check_string(char *str)
{
	int	i;
	int	ret;

	i = -1;
	ret = 0;
	while (str[++i] == ' ')
		;
	if (str[i] == 'e')
	{
		if (ft_strncmp((str+i), "echo", 4) == 0)
			return (ret);
	}
	i = -1;
	while (str[++i])
	{
		if (str[i] == '>' || str[i] == '<')
			ret = check_string_util(str, &i, str[i]);
		if (ret == 1)
			break;
	}
	if (ret == 1)
		free(g_vars->line);
    return (ret);
}
