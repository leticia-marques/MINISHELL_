/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:03:56 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/28 05:23:44 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

/*void	clear_quote(char **old, char symbol)
{
	int		len;
	int		needle;
	char	*new;

	len = ft_strlen(*old);
	needle = 0;
	new = malloc(sizeof(char) * (len - 1));
	while ((*old)[needle + 1])
	{
		if ((*old)[needle + 1] == symbol)
			break ;
		new[needle] = (*old)[needle + 1];
		needle++;
	}
	new[needle] = '\0';
	free(*old);
	*old = new;
}*/

/*static int	find_var_node(t_node **aux, char **line, int *set)
{
	int		counter;
	t_node	*temp;

	counter = 0;
	temp = *aux;
	while (temp)
	{
		if ((temp)->val.str[0] == '\"')
		{
			clear_quote(&temp->val.str, '\"');
			(*line) = getenv((temp)->val.str + 1);
			*set = 1;
		}
		else if ((temp)->val.str[0] == '$')
		{
			(*line) = getenv((temp)->val.str + 1);
			*set = 1;
		}
		else if ((temp)->val.str[0] == '\'')
			clear_quote(&temp->val.str, '\'');
		(temp) = (temp)->next;
		counter++;
		if ((*line) != NULL)
			break ;
	}
	return (counter);
}

void	var_expansion(t_node **cmd)
{
	t_node	*aux;
	int		i;
	char	*line;
	int		counter;
	int		set;

	aux = (*cmd)->first_arg;
	line = NULL;
	set = 0;
	counter = 0;
	counter = find_var_node(&aux, &line, &set);
	if (set == 1)
	{
		if (line == NULL)
			line = "";
		if (line != NULL)
		{
			aux = (*cmd)->first_arg;
			i = 0;
			while (++i < counter && aux != NULL)
				aux = aux->next;
			free(aux->val.str);
			set_value_str(aux, line);
		}
	}
}*/
void	check_char(t_format *data, char *old, int len);

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

void	expand_var(t_format *data, char *old, int len, char symbol)
{
	char	*var;
	int		var_len;
	char	*expanded;
	char	*temp;

	if (symbol == '\"')
		data->old_needle++;
	var = ft_calloc(sizeof(char), strlen(old + data->old_needle));
	var_len = 0;
	while (old[data->old_needle] != symbol && old[data->old_needle] != '\0' && \
		old[data->old_needle] != '\'' && old[data->old_needle] != '\"')
	{
		copy_and_walk(&var, &old, &var_len, &data->old_needle);
		if (ft_isalpha(old[data->old_needle]) == 0 \
			&& old[data->old_needle] != '$')
			break ;
	}
	var[var_len] = '\0';
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
	}
	else if (old[data->old_needle] == '$' && old[data->old_needle + 1] \
		!= '?' && old[data->old_needle + 1] != '\0')
	{
		if (old[data->old_needle + 1] != '\"')
			expand_var(data, old, len, ' ');
		else
		{
			get_space(&data->new, data->new_needle, data->old_needle, len);
			copy_and_walk(&data->new, &old, \
				&data->new_needle, &data->old_needle);
		}
	}
	else
	{
		get_space(&data->new, data->new_needle, data->old_needle, len);
		copy_and_walk(&data->new, &old, &data->new_needle, &data->old_needle);
	}
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
