/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:15:31 by william           #+#    #+#             */
/*   Updated: 2023/09/22 09:23:49 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	handle_sigusr(int signum, siginfo_t *info, void *ucontent)
{
	static int				bit_itr;
	static unsigned char	c;

	bit_itr = -1;
	(void)ucontent;
	if (bit_itr < 0)
		bit_itr = 7;
	if (signum == SIGUSR1)
		c |= (1 << bit_itr);
	bit_itr--;
	if (bit_itr < 0 && c)
	{
		ft_putchar_fd(c, STDOUT_FILENO);
		c = 0;
		if (kill(info->si_pid, SIGUSR2) == -1)
			ft_error_handler("Server failed to send SIGUSR2");
		return ;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		ft_error_handler("Failed to send SIGUSR1");
}

void	configure_sigaction(void)
{
	struct sigaction	sa_newsignal;

	sa_newsignal.sa_sigaction = &handle_sigusr;
	sa_newsignal.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa_newsignal, NULL) == -1)
		ft_error_handler("Failed to configure SIGUSR1\n");
	if (sigaction(SIGUSR2, &sa_newsignal, NULL) == -1)
		ft_error_handler("Failed to configure SIGUSR2\n");
}

int	main(void)
{
	pid_t	server_pid;

	server_pid = getpid();
	ft_printf("Server PID: %d\n", (int)server_pid);
	ft_printf("Waiting for signals...\n");
	while (1)
	{
		configure_sigaction();
	}
	return (EXIT_SUCCESS);
}
