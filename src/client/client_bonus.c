/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 08:20:22 by wiferrei          #+#    #+#             */
/*   Updated: 2023/10/02 16:13:01 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk_bonus.h"

/*
Handles the SIGUSR2 signal indicating the server has 
successfully received the message, then prints confirmation 
and terminates the client.
*/
void	ft_handler(int signal)
{
	if (signal == SIGUSR2)
	{
		ft_putstr_fd("Message received\n", 1);
		exit(0);
	}
}

/*
Check if the string is composed only of digits characters
*/
int	ft_str_is_digit(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

/*
For each bit of the unsigned integer 'c', sends a signal (SIGUSR1 or SIGUSR2) 
to the server, depending on whether the bit is 0 or 1. The function 
continuously sends all bits of the given integer.
*/
void	ft_send_bit(unsigned int c, int pid_id, int msg_size)
{
	int	bit;
	int	usleep_time;

	usleep_time = 250 + (msg_size * 5);
	bit = -1;
	while (++bit < 8)
	{
		if ((c >> bit & 1) && kill(pid_id, SIGUSR1) == -1)
			ft_error_exit("Error: Failed to send SIGUSR1 signal");
		else if (!(c >> bit & 1) && kill(pid_id, SIGUSR2) == -1)
			ft_error_exit("Error: Failed to send SIGUSR2 signal");
		usleep(usleep_time);
	}
}

/*
Sends each character of the provided message to the server using 
the ft_send_bit function. After the entire message is sent, it sends 
a null character to signal the end of the message.
*/
void	ft_send_message(char *txt, int pid_id)
{
	int	i;
	int	msg_length;

	msg_length = ft_strlen(txt);
	i = 0;
	while (txt[i])
	{
		ft_send_bit(txt[i], pid_id, msg_length);
		i++;
	}
	ft_send_bit(txt[i], pid_id, msg_length);
}

/*
The main function of the client:
- Checks if the provided PID is a valid number.
- Checks if the provided PID corresponds to a running process.
- If the correct arguments are provided, it sets up the signal handler
  and sends the message to the server.
- After sending, it goes into a pause loop awaiting acknowledgment.
*/
int	main(int ac, char **av)
{
	if (!ft_str_is_digit(av[1]))
	{
		ft_error_exit("(Error) PID must be a number\n");
		return (EXIT_FAILURE);
	}
	if (kill(ft_atoi(av[1]), 0) == -1)
		ft_error_exit("Error: Invalid PID or Process not running");
	if (ac == 3)
	{
		signal(SIGUSR2, ft_handler);
		ft_send_message(av[2], ft_atoi(av[1]));
		while (1)
			pause();
	}
	else
		ft_error_exit("(Error) Try ./client <PID> <MSG>\n");
	return (EXIT_SUCCESS);
}
