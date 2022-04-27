/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarque <lemarque@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:25:49 by lemarque          #+#    #+#             */
/*   Updated: 2022/04/27 18:16:03 by lemarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_vars	*vars;

static void	parse_and_call_exec_aux(int i, t_input	*source, t_node	*cmd)
{
	if (i == 1)
		check_cmd(cmd, vars->env);
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
	i = check_argv(&cmd, &source);
	if (source.position >= source.line_size)
	{
		signal(SIGQUIT, signal_aborted);
		if (i == 1)
			exec_last_cmd(cmd, vars->env);
		free(source.line);
		// if (cmd)
		// 	free_node(cmd);
		return ;
	}
	else
	{
		parse_and_call_exec_aux(i, &source, cmd);
		if (cmd)
			free_node(cmd);
		parse_and_call_exec((char *)(source.line + source.position), holder);
	}
}

static void	read_prompt(t_token_holder *holder)
{
	while (1)
	{
		signal_treatment();
		vars->line = NULL;
		vars->line = readline(vars->prompt);
		if (vars->line != NULL)
		{
			if (ft_strcmp(vars->line, "exit") == 0)
			{
				free_vars_and_holder(holder);
				printf("exit\n");
				exit(5);
			}
			add_history(vars->line);
			if (!(ft_strcmp(vars->line, "") == 0))
				parse_and_call_exec(vars->line, holder);
			free(vars->line);
			vars->count = 1;
		}
		else if (vars->line == NULL)
		{
			write(1, "exit\n", 5);
			break ;
		}
		dup2(vars->save_stdin, 0);
		dup2(vars->save_stdout, 1);
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
