/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:15:31 by william           #+#    #+#             */
/*   Updated: 2023/09/21 09:29:50 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int		g_received = 0;

void	handle_sigusr(int signum, siginfo_t *siginfo, void *context)
{
	(void)context;
	if (signum == SIGUSR1)
	{
		g_received = 1;
		ft_printf("Received SIGUSR1 from PID: %d\n", siginfo->si_pid);
	}
	else if (signum == SIGUSR2)
	{
		g_received = 2;
		ft_printf("Received SIGUSR2 from PID: %d\n", siginfo->si_pid);
	}
	else
		ft_printf("Received signal: %d\n", signum);
}

void	configure_sigaction(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &handle_sigusr;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	{
		ft_error_handler("Failed to configure SIGUSR1\n");
		return (1);
	}
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_error_handler("Failed to configure SIGUSR2\n");
		return (1);
	}
}

int	main(void)
{
	pid_t	server_pid;

	server_pid = getpid();
	ft_printf("Server PID: %d\n", (int)server_pid);
	ft_printf("Waiting for signals...\n");
	while (1)
	{
		if (g_received == 1)
		{
			ft_printf("Received 1\n");
			g_received = 0;
		}
		else if (g_received == 2)
		{
			ft_printf("Received 0\n");
			g_received = 0;
		}
	}
	return (EXIT_SUCCESS);
}
