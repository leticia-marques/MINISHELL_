/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 19:55:44 by lemarque          #+#    #+#             */
/*   Updated: 2022/05/07 04:47:24 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	is_all_space(void)
{
	int	i;

	i = -1;
	while (g_vars->line[++i])
	{
		if (g_vars->line[i] != ' ')
			return (0);
	}
	free(g_vars->line);
	return (1);
}

static int	check_string_util(char *str, int *i, char c)
{
	if (str[*i + 1] && str[*i + 1] == c)
		*i += 1;
	while (str[++*i] == ' ' && str[*i])
		;
	if (str[*i] == '<' || str[*i] == '>' || str[*i] == '\0')
	{
		redirect_error(str + *i);
		return (1);
	}
	return (0);
}

int	check_string(char *str)
{
	int	i;
	int	ret;

	i = -1;
	ret = 0;
	while (str[++i] == ' ')
		;
	if (str[i] == 'e')
	{
		if (ft_strncmp((str + i), "echo", 4) == 0)
			return (ret);
	}
	i = -1;
	while (str[++i])
	{
		if (str[i] == '>' || str[i] == '<')
			ret = check_string_util(str, &i, str[i]);
		if (ret == 1)
			break ;
	}
	if (ret == 1)
		free(g_vars->line);
	return (ret);
}
