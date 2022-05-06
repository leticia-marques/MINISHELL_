/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 20:14:19 by lemarque          #+#    #+#             */
/*   Updated: 2022/05/04 18:58:00 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static int	echo_loop(int fd[2], int position, t_node *aux)
{
	int	i;

	i = 0;
	while (aux && ft_strcmp(aux->val, ">") != 0)
	{
		if (ft_strcmp(aux->val, "\'") == 0 || \
			ft_strcmp(aux->val, "\"") == 0)
		{
			free(aux->val);
			aux->val = ft_strdup("");
		}
		if (ft_strcmp(aux->val, "-n") == 0)
		{
			i = 1;
			aux = aux->next;
			continue ;
		}
		if (position)
			ft_putstr_fd(aux->val, 1);
		else
			ft_putstr_fd(aux->val, fd[1]);
		aux = aux->next;
	}
	return (i);
}

int	check_echo(t_node **cmd, t_input **src)
{
	t_node	*aux;
	int		i;
	int		fd[2];
	int		position;

	position = (*src)->position >= (*src)->line_size;
	if (pipe(fd) == -1)
		perror("error:");
	aux = (*cmd)->first_arg->next;
	i = echo_loop(fd, position, aux);
	if (i != 1)
	{
		if (position)
			ft_putchar_fd('\n', 1);
		else
			ft_putchar_fd('\n', fd[1]);
	}
	if (!position)
		dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
	g_vars->exit_code = 0;
	return (0);
}
