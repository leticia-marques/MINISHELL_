/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 20:14:19 by lemarque          #+#    #+#             */
/*   Updated: 2022/05/07 04:39:48 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static void	echo_loop_util(int fd[2], int position, t_node *aux)
{
	if (position)
	{
		ft_putstr_fd(aux->val, 1);
		ft_putchar_fd(' ', 1);
	}
	else
	{
		ft_putstr_fd(aux->val, fd[1]);
		ft_putchar_fd(' ', fd[1]);
	}
}

static int	echo_loop(int fd[2], int position, t_node *aux, t_node **cmd)
{
	int	i;

	i = 0;
	while (aux)
	{
		if ((*cmd)->outfile != -1 && (ft_strcmp(aux->val, ">") == 0 \
			|| ft_strcmp(aux->val, ">>") == 0))
			break ;
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
		echo_loop_util(fd, position, aux);
		aux = aux->next;
	}
	return (i);
}

static void	echo_util(int fd[2], int i, int position)
{
	if (i != 1)
	{
		if (position)
			ft_putchar_fd('\n', 1);
		else
			ft_putchar_fd('\n', fd[1]);
	}
}

int	check_echo(t_node **cmd, t_input **src)
{
	t_node	*aux;
	int		i;
	int		fd[2];
	int		position;

	if ((*cmd)->outfile == -1)
	{
		dup2(g_vars->save_stdin, 0);
		dup2(g_vars->save_stdout, 1);
	}
	position = (*src)->position >= (*src)->line_size;
	if (pipe(fd) == -1)
		perror("error:");
	aux = (*cmd)->first_arg->next;
	i = echo_loop(fd, position, aux, cmd);
	echo_util(fd, i, position);
	if (!position)
		dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
	g_vars->exit_code = 0;
	return (0);
}
