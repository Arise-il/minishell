/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 09:03:46 by oouhlale          #+#    #+#             */
/*   Updated: 2025/06/02 14:21:09 by oouhlale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_clear(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		free(env->value);
		env = env->next;
		free(tmp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_cmd	*cmd_list;
	int		last_exit_status;
	t_mini	mini;
	
	cmd_list = NULL;
	env_init(&mini, envp);
	(void)argc;
	(void)argv;
	last_exit_status = 0;
	using_history();
	setup_signals();
	disable_ctrl_echo();
	rl_bind_key('\t', rl_complete);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		add_history(input);
		if (!*input || only_spaces(input) || check_unclosed_quotes(input))	
			continue ;
		cmd_list = parse_input(input, mini.env, last_exit_status);
		if (cmd_list)
			print_cmds(cmd_list);
		if (!cmd_list)
			mini.exit_status = 1 ;
		else if (!cmd_list->args || !cmd_list->args[0] || cmd_list->args[0][0] == '\0')
			mini.exit_status = 0;
		else
			execute_commands(cmd_list, &mini);
		last_exit_status = mini.exit_status;
		//ft_malloc(0, 0);
		free(input);
	}
	//env_clear(mini.env);
	ft_malloc(0, 0);
	rl_clear_history();
	return (0);
}
