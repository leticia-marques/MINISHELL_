/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 23:32:04 by lemarque          #+#    #+#             */
/*   Updated: 2022/05/09 19:06:20 by lemarque         ###   ########.fr       */
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
	(void)sig;
	write(1, "Quit (core dumped) e coisas\n", 28);
	return ;
}

void	here_doc_sig(int sig)
{
	g_vars->exit_code = 130;
	(void)sig;
	write(1, "\n", 1);
	exit (130);
}
