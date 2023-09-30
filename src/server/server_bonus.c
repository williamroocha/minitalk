/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 08:19:44 by wiferrei          #+#    #+#             */
/*   Updated: 2023/09/30 21:32:51 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk_bonus.h"


void	handler_sig(int signal, siginfo_t *info, void *context)
{
	static unsigned int	c;
	static int			bit;

	(void)context;
	c = (signal == SIGUSR1) << bit | c;
	bit++;
	if (bit == 8)
	{
		if (!c)
			kill(info->si_pid, SIGUSR2);
		else
			ft_putchar_fd(c, 1);
		bit = 0;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	sig;

	ft_printf("Server PID: %d\n", getpid());
	sig.sa_sigaction = handler_sig;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sig, 0) == -1)
		ft_error_exit("Error: Failed to set SIGUSR1 handler");
	if (sigaction(SIGUSR2, &sig, 0) == -1)
		ft_error_exit("Error: Failed to set SIGUSR2 handler");
	while (1)
		pause();
}
