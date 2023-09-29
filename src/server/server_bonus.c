/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 08:19:44 by wiferrei          #+#    #+#             */
/*   Updated: 2023/09/29 08:55:57 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk_bonus.h"

// Signal handler for SIGUSR1 and SIGUSR2
void	handler_sig(int signal, siginfo_t *info, void *context)
{
	static unsigned int		c;
	static int				bit;
	static unsigned char	bytes[4];
	static int				byte_index;
	int						i;

	// static variables to store the currently building character and the bit position
	byte_index = 0;
	(void)context;
	// If SIGUSR1 is received, add the current bit to the character. Else,
		keep it as is.
	c = (signal == SIGUSR1) << bit | c;
	bit++;
	// When we've received 8 bits (1 byte)
	if (bit == 8)
	{
		bytes[byte_index] = (unsigned char)c;
		byte_index++;
		// Determine if this is the last byte for the current Unicode character
		if ((bytes[0] >> 7) == 0x0 || (byte_index == 2
				&& (bytes[0] >> 5) == 0x6) || (byte_index == 3
				&& (bytes[0] >> 4) == 0xE) || (byte_index == 4
				&& (bytes[0] >> 3) == 0x1E))
		{
			if (!c)
			{
				// Send acknowledgment to client if it's the end of message
				kill(info->si_pid, SIGUSR2);
			}
			else
			{
				// Print the Unicode character and reset bytes using a while loop
				i = 0;
				while (i < byte_index)
				{
					write(1, &bytes[i], 1);
					i++;
				}
			}
			byte_index = 0;
		}
		// Reset the bit counter and character for the next byte
		bit = 0;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	sig;

	// Print the PID for the client to know
	ft_printf("Server PID: %d\n", getpid());
	// Set up the signal handler for SIGUSR1 and SIGUSR2
	sig.sa_sigaction = handler_sig;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sig, 0);
	sigaction(SIGUSR2, &sig, 0);
	// Keep the server running indefinitely
	while (1)
		usleep(100);
}
