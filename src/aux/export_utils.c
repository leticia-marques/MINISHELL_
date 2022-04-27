/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:00:23 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/11 06:48:00 by coder            ###   ########.fr       */
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

void	write_to_pipe(char **new_env)
{
	int	i;
	int	fd[2];

	if (pipe(fd) == -1)
		perror("error:");
	i = -1;
	while (new_env[++i] != NULL)
	{
		new_env[i] = ft_strjoin("Declare -x ", new_env[i]);
		if (!new_env)
			return ;
		printf("%s\n", new_env[i]);
		write(fd[1], new_env[i], ft_strlen(new_env[i]));
		write(fd[1], "\n", ft_strlen(new_env[i]));
	}
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
}
