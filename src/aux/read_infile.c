/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_infile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 19:02:40 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/22 17:02:51 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static void handling_signal(int sig)
{
	vars->exit_code = 130;
	(void)sig;
	write(1, "\n", 1);
	exit (130);
}

void	read_infile(void)
{
	char	*line;
	int i;

	i = fork();
	if (i == 0)
	{
		signal(SIGINT, handling_signal);
		while (1)
		{
			line = readline("");
			if(ft_strcmp(line, "") == 0)
				printf("\n");
			break;
		}
		vars->exit_code = 0;
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		wait(NULL);
	}
}
