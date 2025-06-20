/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 09:03:46 by oouhlale          #+#    #+#             */
/*   Updated: 2025/06/20 11:53:47 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
void update_pwd_env(t_env **env)
{
    char *cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        // getcwd failed: directory deleted or inaccessible
        perror("minishell: getcwd");
        return;
    }
    char *pwd_str = ft_strjoin("PWD=", cwd);
    free(cwd);
    if (!pwd_str)
        return;
    if (env_update(pwd_str, *env) == ERROR)
        env_add(pwd_str, *env);
    free(pwd_str);
}


void check_cwd_and_recover(t_env **env)
{
    char *cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        ft_putendl_fd("minishell: warning: current directory deleted or inaccessible", 2);
        char *home = get_env_value("HOME", *env);
        if (home && chdir(home) == 0)
            update_pwd_env(env);
        else if (chdir("/") == 0)
            update_pwd_env(env);
        else
            ft_putendl_fd("minishell: fatal: cannot recover current directory", 2);
    }
    else
    {
        free(cwd);
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
		//check_cwd_and_recover(&mini.env);
		input = readline("minishell$ ");
		if (!input)
			break ;
		add_history(input);
		if (!*input || only_spaces(input) || check_unclosed_quotes(input))	
			continue ;
		cmd_list = parse_input(input, mini.env, last_exit_status);
		// if (cmd_list)
		// 	print_cmds(cmd_list);
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
	ft_malloc(0, 0);
	rl_clear_history();
	return (0);
}
