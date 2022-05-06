/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:25:49 by lemarque          #+#    #+#             */
/*   Updated: 2022/05/05 23:05:11 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_vars	*g_vars;

static void	parse_and_call_exec_aux(int i, t_input	*source, t_node	*cmd)
{
	if (i == 1)
		check_cmd(cmd, g_vars->env);
	source->position++;
}

static void	parse_and_call_exec(char *line, t_token_holder *holder)
{
	t_node	*cmd;
	t_input	source;
	int		i;

	init_src(&source, line);
	skip_white_spaces(&source);
	cmd = parser_command(&source, holder);
	if (cmd == NULL)
		return ;
	i = check_argv(&cmd, &source, holder);
	if (source.position >= source.line_size)
	{
		signal(SIGQUIT, signal_aborted);
		if (i == 1)
			exec_last_cmd(cmd, g_vars->env);
		free(source.line);
		// if (cmd)
		// 	free_node(&cmd);
		return ;
	}
	else
	{
		parse_and_call_exec_aux(i, &source, cmd);
		parse_and_call_exec((char *)(source.line + source.position), holder);
		if (cmd)
			free_node(&cmd);
	}
}

static void	read_prompt_aux(t_token_holder *holder)
{
	free_vars_and_holder(holder);
	printf("exit\n");
	exit(5);
}

static int	is_all_space()
{
	int	i;
	i = -1;
	while(g_vars->line[++i])
	{
		if (g_vars->line[i] != ' ')
			return (0);
	}
	free(g_vars->line);
	return (1);
}

static void	read_prompt(t_token_holder *holder)
{
	while (1)
	{
		signal_treatment();
		g_vars->line = NULL;
		g_vars->line = readline(g_vars->prompt);
		if (g_vars->line != NULL && is_all_space() == 0)
		{
			if (ft_strcmp(g_vars->line, "exit") == 0)
				read_prompt_aux(holder);
			add_history(g_vars->line);
			if (!(ft_strcmp(g_vars->line, "") == 0))
				parse_and_call_exec(g_vars->line, holder);
			free(g_vars->line);
		}
		else if (g_vars->line == NULL)
		{
			write(1, "exit\n", 5);
			break ;
		}
		dup2(g_vars->save_stdin, 0);
		dup2(g_vars->save_stdout, 1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_token_holder	holder;

	(void)argc;
	(void)argv;
	init_holder(&holder);
	init_vars(envp);
	read_prompt(&holder);
	free_vars_and_holder(&holder);
	rl_clear_history();
}
