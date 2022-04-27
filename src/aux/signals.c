/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 23:32:04 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/23 21:59:50 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static void	handling(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_treatment(void)
{
	signal(SIGINT, handling);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_aborted(int sig)
{
	vars->exit_code = 127;
	(void)sig;
	write(1, "Quit (core dumped)\n", 19);
	return ;
}
