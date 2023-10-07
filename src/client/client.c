/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:45:27 by wiferrei          #+#    #+#             */
/*   Updated: 2023/10/07 19:55:27 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

/*
** Checks whether the string consists only of digit characters.
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
** Sends each bit of the character 'c' as a signal (SIGUSR1 or SIGUSR2)
** to the server. Whether the bit is 0 or 1 determines the signal type.
** Continuously sends all bits of the character.
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
** Sends each character of the message to the server using
** the ft_send_bit function. Once the message is sent,
** it signals the end of the message by sending a null character.
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
** Main function of the client:
** 1. Validates the PID.
** 2. Checks the process associated with the PID.
** 3. If correct arguments are provided, sends the message to the server.
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
		ft_send_message(av[2], ft_atoi(av[1]));
	else
		ft_error_exit("(Error) Try ./client <PID> <MSG>\n");
	return (EXIT_SUCCESS);
}
