/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josmanov <josmanov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:33:39 by josmanov          #+#    #+#             */
/*   Updated: 2025/02/01 00:12:28 by josmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static t_server	g_server_data;

static void	reset_data(void)
{
	g_server_data.bit_count = 0;
	g_server_data.c = 0;
	g_server_data.client_pid = 0;
}

static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (!g_server_data.client_pid)
		g_server_data.client_pid = info->si_pid;
	if (sig == SIGUSR1)
		g_server_data.c |= (1 << (7 - g_server_data.bit_count));
	else
		g_server_data.c &= ~(1 << (7 - g_server_data.bit_count));
	g_server_data.bit_count++;
	if (g_server_data.bit_count == 8)
	{
		if (g_server_data.c)
			ft_putchar_fd(g_server_data.c, 1);
		reset_data();
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
	{
		ft_putstr_fd("Error sending acknowledgment signal\n", 2);
		exit(2);
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	reset_data();
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_putstr_fd("Failed to set up SIGUSR1 handler\n", 2);
		exit(2);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_putstr_fd("Failed to set up SIGUSR2 handler\n", 2);
		exit(2);
	}
	while (1)
		pause();
	return (0);
}
