/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 08:19:44 by wiferrei          #+#    #+#             */
/*   Updated: 2023/10/02 16:10:20 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk_bonus.h"

/*
This function handles incoming signals from the client. 
For every bit received from the client, it accumulates the 
bits to form a character. When all 8 bits of a character 
are received, it either prints the character or, in the 
case of a null character, acknowledges the receipt of the 
entire message to the client and starts a new line.
*/
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
		{
			kill(info->si_pid, SIGUSR2);
			ft_putchar_fd('\n', 1);
		}
		else
			ft_putchar_fd(c, 1);
		bit = 0;
		c = 0;
	}
}

/*
The main function initializes the server:
- Prints its own PID so that clients can send messages to it.
- Sets up a signal handler to handle incoming signals (bits) from clients.
- Continuously waits for signals using a pause loop.
*/
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
