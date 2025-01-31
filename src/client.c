/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josmanov <josmanov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:45:11 by josmanov          #+#    #+#             */
/*   Updated: 2025/02/01 00:20:00 by josmanov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static volatile sig_atomic_t	g_server_ack;

static void	ft_exit_error(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(2);
}

static void	send_bit(pid_t pid, int bit)
{
	int	signal;

	if (bit)
		signal = SIGUSR1;
	else
		signal = SIGUSR2;
	if (kill(pid, signal) == -1)
		ft_exit_error("Error sending signal\n");
	while (!g_server_ack)
	{
		usleep(100);
	}
	g_server_ack = 0;
	usleep(100);
}

static void	sig_handler(int sig)
{
	(void)sig;
	g_server_ack = 1;
}

static void	send_message(pid_t pid, char *str)
{
	int		i;
	char	c;

	while (*str)
	{
		i = 8;
		c = *str++;
		while (i--)
			send_bit(pid, (c >> i) & 1);
	}
	i = 8;
	while (i--)
		send_bit(pid, 0);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (argc != 3 || !ft_is_str_digit(argv[1]))
		ft_exit_error("Usage: ./client [PID] [MESSAGE]\n");
	sa.sa_handler = sig_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		ft_exit_error("Failed to set up signal handler\n");
	send_message(ft_atoi(argv[1]), argv[2]);
	return (0);
}
