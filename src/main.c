/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 09:03:46 by oouhlale          #+#    #+#             */
/*   Updated: 2025/07/03 14:52:30 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_ctrl_c = 0;

int	init_minishell(t_mini *mini, char **envp)
{
	mini->env = NULL;
	env_init(mini, envp);
	increment_shell_level(mini->env);
	using_history();
	setup_signals();
	rl_bind_key('\t', rl_complete);
	return (0);
}

void	handle_signals(int *last_exit_status)
{
	if (g_ctrl_c)
	{
		g_ctrl_c = 0;
		*last_exit_status = 130;
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
}

int	should_skip_input(char *input)
{
	return (!*input || only_spaces(input) || check_unclosed_quotes(input));
}

void	process_input(char *input, t_mini *mini, int *last_exit_status)
{
	t_cmd	*cmd_list;

	cmd_list = parse_input(input, mini->env, *last_exit_status);
	if (!cmd_list)
		mini->exit_status = 1;
	else if (!cmd_list->args
		|| !cmd_list->args[0]
		|| cmd_list->args[0][0] == '\0')
		mini->exit_status = 0;
	if (cmd_list && cmd_list->is_interrupted != 1)
		execute_commands(cmd_list, mini);
	*last_exit_status = mini->exit_status;
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	int		last_exit_status;
	t_mini	mini;

	(void)argc;
	(void)argv;
	last_exit_status = 0;
	init_minishell(&mini, envp);
	while (1)
	{
		signal(SIGINT, handle_sigint);
		input = readline("minishell$ ");
		handle_signals(&last_exit_status);
		if (!input)
			break ;
		add_history(input);
		if (should_skip_input(input))
			continue ;
		process_input(input, &mini, &last_exit_status);
		free(input);
	}
	ft_malloc(0, 0);
	rl_clear_history();
	return (0);
}
