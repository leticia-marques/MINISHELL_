/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinacio- < jinacio-@student.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:03:56 by lemarque          #+#    #+#             */
/*   Updated: 2022/05/03 19:16:00 by jinacio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static char	*find_var(char *var)
{
	char	*line;
	int		i;

	i = -1;
	line = NULL;
	if (var != NULL)
	{
		while (vars->env[++i] != NULL)
		{
			if (ft_strncmp(vars->env[i], var, ft_strlen(var)) == 0)
			{
				if (vars->env[i][ft_strlen(var)] == '=')
				{
					line = vars->env[i] + ft_strlen(var) + 1;
					break ;
				}
			}
		}
	}
	if (line != NULL)
		return (line);
	return ("");
}

static char	*expand_loop(t_format *data, char *old, char *symbol)
{
	int		var_len;
	char	*var;

	var_len = 0;
	var = ft_calloc(sizeof(char), strlen(old + data->old_needle));
	while (old[data->old_needle] != *symbol && old[data->old_needle] != '\0' \
		&& old[data->old_needle] != '\'' && old[data->old_needle] != '\"')
	{
		copy_and_walk(&var, &old, &var_len, &data->old_needle);
		if (ft_isalpha(old[data->old_needle]) == 0 \
			&& old[data->old_needle] != '$')
			break ;
	}
	var[var_len] = '\0';
	return (var);
}

void	expand_var(t_format *data, char *old, int len, char symbol)
{
	char	*var;
	char	*expanded;
	char	*temp;

	if (symbol == '\"')
		data->old_needle++;
	var = expand_loop(data, old, &symbol);
	if (symbol == '\"')
		data->old_needle++;
	expanded = find_var(var + 1);
	free(var);
	temp = ft_strjoin(data->new, expanded);
	free(data->new);
	data->new = ft_strdup(temp);
	free(temp);
	data->new_needle += ft_strlen(expanded);
	get_space(&data->new, data->new_needle, data->old_needle, len);
}

void	check_char(t_format *data, char *old, int len)
{
	if (old[data->old_needle] == '\'' && old[data->old_needle + 1] != '\'')
		clear_quotes(data, old, len, '\'');
	else if (old[data->old_needle] == '\"' && old[data->old_needle + 1] != '$')
		clear_quotes(data, old, len, '\"');
	else if (old[data->old_needle] == '\"' && old[data->old_needle + 1] == '$' \
		&& old[data->old_needle + 2] != '\"' && \
		old[data->old_needle + 2] != ' ')
	{
		if (old[data->old_needle + 2] != '?' )
			expand_var(data, old, len, '\"');
		else
			get_space_and_clear_quotes(data, len, &old);
	}
	else if (old[data->old_needle] == '$' && old[data->old_needle + 1] \
		!= '?' && old[data->old_needle + 1] != '\0')
	{
		if (old[data->old_needle + 1] != '\"')
			expand_var(data, old, len, ' ');
		else
			get_space_and_clear_quotes(data, len, &old);
	}
	else
		get_space_and_clear_quotes(data, len, &old);
	if (old[data->old_needle] == '\0')
		data->new[data->new_needle] = '\0';
}

char	*format_line(char *old, int len)
{
	t_format	*data;
	char		*tmp;

	data = malloc(sizeof(t_format));
	data->old_needle = 0;
	data->new_needle = 0;
	data->new = ft_calloc(sizeof(char), len + 1);
	if (data->new == NULL)
		return (old);
	while (old[data->old_needle] != '\0')
	{
		if (old[data->old_needle] == ' ' && old[data->old_needle + 1] == ' ')
			data->old_needle++;
		if ((old[data->old_needle] == 'e' && old[data->old_needle + 1] == 'x')
			|| (old[data->old_needle] == 'u' \
			&& old[data->old_needle + 1] == 'n'))
			check_unset_export(&data, old, len);
		else
			check_char(data, old, len);
	}
	tmp = data->new;
	free(data);
	return (tmp);
}
