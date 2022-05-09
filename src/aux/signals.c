/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 23:32:04 by lemarque          #+#    #+#             */
/*   Updated: 2022/05/09 22:54:54 by coder            ###   ########.fr       */
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
	g_vars->exit_code = 131;
	(void)sig;
	write(1, "Quit (core dumped)\n", 19);
	return ;
}

void	here_doc_sig(int sig)
{
	g_vars->exit_code = 130;
	(void)sig;
	write(1, "\n", 1);
	exit (130);
}
