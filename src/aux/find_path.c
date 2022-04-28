/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 23:01:10 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/28 04:54:48 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static void	*add_slash(char *str)
{
	char	*tmp;

	tmp = str;
	str = ft_strjoin(tmp, "/");
	if (!str)
		return (NULL);
	return (str);
}

static char	**extract_paths(void)
{
	char	**splitted_path;
	char	*path;
	int		i;

	i = -1;
	while (vars->env[++i])
	{
		if (ft_strncmp("PATH=", vars->env[i], 5) == 0)
		{
			path = ft_strdup(&vars->env[i][5]);
			splitted_path = ft_split(path, ':');
			free(path);
			if (!splitted_path)
				return (NULL);
			i = 0;
			while (splitted_path[i] != NULL)
			{
				splitted_path[i] = add_slash(splitted_path[i]);
				i++;
			}
			return (splitted_path);
		}
	}
	return (NULL);
}

static char	*check_absolute_path(char *cmd)
{
	if (!cmd)
		return (cmd);
	else if (ft_strchr(cmd, '/') && access(cmd, F_OK | X_OK) == 0)
	{
		cmd_path = ft_strdup(cmd);
		return (cmd_path);
	}
	return (NULL);
}

char	*find_path(char *cmd)
{
	char	*cmd_path;
	char	**splited_path;
	int		i;

	check_absolute_path(cmd);
	i = -1;
	splited_path = extract_paths();
	if (splited_path)
	{
		while (splited_path[++i] != NULL)
		{
			cmd_path = ft_strjoin(splited_path[i], cmd);
			if (!cmd_path)
				continue ;
			if (access(cmd_path, F_OK | X_OK) == 0)
			{
				ft_split_free(splited_path);
				return (cmd_path);
			}
			free(cmd_path);
		}
	}
	command_not_found(cmd, splited_path);
	return (NULL);
}
