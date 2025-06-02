/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouhlale <oouhlale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:30:59 by oouhlale          #+#    #+#             */
/*   Updated: 2025/06/01 15:59:39 by oouhlale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int g_heredoc_interrupted;

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

// void	handle_sigint_heredoc(int sig)
// {
// 	(void)sig;
// 	g_heredoc_interrupted = 1;
// 	write(1, "\n", 1);
// 	close(0); // Force readline to return NULL
// }

// void	setup_heredoc_signals(void)
// {
// 	signal(SIGINT, handle_sigint_heredoc);
// 	signal(SIGQUIT, SIG_IGN);
// }

// void	restore_signals(void)
// {
// 	signal(SIGINT, SIG_DFL);
// 	signal(SIGQUIT, SIG_DFL);
// }