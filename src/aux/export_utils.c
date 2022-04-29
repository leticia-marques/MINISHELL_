/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:00:23 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/28 22:42:22 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	order_env(char **new_env)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	while (new_env[++i] != NULL)
	{
		j = i;
		while (new_env[++j] != NULL)
		{
			tmp = new_env[i];
			if (ft_strcmp(new_env[i], new_env[j]) > 0)
			{
				new_env[i] = new_env[j];
				new_env[j] = tmp;
			}
		}
	}
}

void	write_to_pipe(char **new_env, t_input *src)
{
	int	i;
	int	fd[2];
	int	position;

	position = src->position >= src->line_size;
	if (pipe(fd) == -1)
		perror("error:");
	i = -1;
	while (new_env[++i] != NULL)
	{
		new_env[i] = ft_strjoin("Declare -x ", new_env[i]);
		if (!new_env)
			return ;
		if (position)
			ft_putendl_fd(new_env[i], 1);
		else
			ft_putendl_fd(new_env[i], fd[1]);
	}
	if (!position)
		dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
}
