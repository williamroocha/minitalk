/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:15:31 by william           #+#    #+#             */
/*   Updated: 2023/09/27 09:42:56 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

void	handle_sigusr(int signum, siginfo_t *info, void *ucontext)
{
	static int				bit_itr;
	static unsigned char	c;

	bit_itr = -1;
	c = 0;
	(void)ucontext;
	if (bit_itr < 0)
		bit_itr = 7;
	if (signum == SIGUSR1)
		c |= (1 << bit_itr);
	bit_itr--;
	if (bit_itr < 0 && c)
	{
		ft_putchar_fd(c, 1);
		c = 0;
		if (kill(info->si_pid, SIGUSR2) == -1)
			ft_putstr_fd("Failed to send confirmation signal (SIGUSR2)", 2);
		fflush(stdout); // Flush output
		return ;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		ft_putstr_fd("Failed to send confirmation signal (SIGUSR1)", 2);
	fflush(stdout); // Flush output
}

void	config_sigaction(void)
{
	struct sigaction	sa_newsig;

	sa_newsig.sa_sigaction = &handle_sigusr;
	sa_newsig.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa_newsig, NULL) == -1)
		ft_putstr_fd("Failed to change SIGUSR1's behavior", 2);
	if (sigaction(SIGUSR2, &sa_newsig, NULL) == -1)
		ft_putstr_fd("Failed to change SIGUSR2's behavior", 2);
}

int	main(void)
{
	pid_t	server_pid;

	server_pid = getpid();
	ft_printf("Server PID: %d\n", server_pid);
	while (1)
	{
		config_sigaction();
	}
	return (0);
}
