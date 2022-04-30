/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 21:13:02 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/04/29 22:42:40 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	copy_and_walk(char **new, char **old, int *new_needle, int *old_needle)
{
	*(*new + *new_needle) = *(*old + *old_needle);
	*old_needle += 1;
	*new_needle += 1;
}

void	get_space(char **new, int new_needle, int old_needle, int len)
{
	char	*aux;
	int		i;

	i = 0;
	aux = ft_calloc(sizeof(char), (new_needle + len - old_needle + 1));
	while (*(*new + i) != '\0')
	{
		aux[i] = *(*new + i);
		i++;
	}
	aux[i] = '\0';
	free(*new);
	*new = aux;
}

void	clear_quotes(t_format *data, char *old, int len, char quote)
{
	if (quote == '\"')
	{
		get_space(&data->new, data->new_needle, data->old_needle, len);
		copy_and_walk(&data->new, &old, &data->new_needle, \
			&data->old_needle);
		while (old[data->old_needle] != '\"' && old[data->old_needle] != '\0')
		{
			if (old[data->old_needle] == '$')
				expand_var(data, old, len, ' ');
			get_space(&data->new, data->new_needle, data->old_needle, len);
			copy_and_walk(&data->new, &old, &data->new_needle, \
			&data->old_needle);
		}
		get_space(&data->new, data->new_needle, data->old_needle, len);
		copy_and_walk(&data->new, &old, &data->new_needle, &data->old_needle);
	}
	else if (quote == '\'')
	{
		get_space(&data->new, data->new_needle, data->old_needle, len);
		copy_and_walk(&data->new, &old, &data->new_needle, &data->old_needle);
		while (old[data->old_needle] != '\'' && old[data->old_needle] != '\0')
			copy_and_walk(&data->new, &old, \
				&data->new_needle, &data->old_needle);
		copy_and_walk(&data->new, &old, &data->new_needle, &data->old_needle);
	}
}

void	get_space_and_clear_quotes(t_format *data, int len, char **old)
{
	get_space(&data->new, data->new_needle, data->old_needle, len);
	copy_and_walk(&data->new, old, &data->new_needle, &data->old_needle);
}

void	check_unset_export(t_format **data, char *old, int len)
{
	int	i;

	i = (*data)->old_needle;
	if (ft_strncmp(old + i, "export", 6) == 0 || \
		ft_strncmp(old + i, "unset", 5) == 0)
	{
		while (old[(*data)->old_needle] != '|' && \
			old[(*data)->old_needle] != '\0')
		{
			get_space(&(*data)->new, (*data)->new_needle, \
				(*data)->old_needle, len);
			copy_and_walk(&(*data)->new, &old, \
				&(*data)->new_needle, &(*data)->old_needle);
		}
		return ;
	}
	check_char(*data, old, len);
}
