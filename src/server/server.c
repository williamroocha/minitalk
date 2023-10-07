/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:02:27 by wiferrei          #+#    #+#             */
/*   Updated: 2023/10/07 19:56:50 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

/*
** Handles incoming signals (SIGUSR1 and SIGUSR2) from the client.
** Constructs characters from the received bits. Once an entire 
** character is constructed, it is printed. A null character signals 
** a new line.
*/

void	ft_handler_sig(int signal, siginfo_t *info, void *context)
{
	static unsigned int	c;
	static int			bit;

	(void)context;
	(void)info;
	c = (signal == SIGUSR1) << bit | c;
	bit++;
	if (bit == 8)
	{
		if (!c)
			ft_putchar_fd('\n', 1);
		else
			ft_putchar_fd(c, 1);
		bit = 0;
		c = 0;
	}
}

/*
** Main function of the server:
** 1. Prints the server's PID.
** 2. Sets up the signal handlers for incoming messages.
** 3. Waits indefinitely for signals from the client.
*/

int	main(void)
{
	struct sigaction	sig;

	ft_printf("Server PID: %d\n", getpid());
	sig.sa_sigaction = ft_handler_sig;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sig, 0) == -1)
		ft_error_exit("Error: Failed to set SIGUSR1 handler");
	if (sigaction(SIGUSR2, &sig, 0) == -1)
		ft_error_exit("Error: Failed to set SIGUSR2 handler");
	while (1)
		pause();
}
