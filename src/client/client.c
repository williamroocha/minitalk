/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiferrei <wiferrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:45:27 by wiferrei          #+#    #+#             */
/*   Updated: 2023/09/30 21:19:55 by wiferrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

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

void	ft_send_bit(unsigned char c, int pid_id)
{
	int	bit;

	bit = -1;
	while (++bit < 8)
	{
		if ((c >> bit & 1) && kill(pid_id, SIGUSR1) == -1)
			ft_error_exit("Error: Failed to send SIGUSR1 signal");
		else if (!(c >> bit & 1) && kill(pid_id, SIGUSR2) == -1)
			ft_error_exit("Error: Failed to send SIGUSR2 signal");
		usleep(250);
	}
}

void	ft_send_message(char *txt, int pid_id)
{
	int	i;

	i = 0;
	while (txt[i])
	{
		ft_send_bit(txt[i], pid_id);
		i++;
	}
	ft_send_bit(txt[i], pid_id);
}

int	main(int ac, char **av)
{
	if (ac != 3)
	{
		ft_error_exit("(Error) Try ./client <PID> <MSG>\n");
		return (EXIT_FAILURE);
	}
	if (!ft_str_is_digit(av[1]))
	{
		ft_error_exit("Error: PID must be a number\n");
		return (EXIT_FAILURE);
	}
	ft_send_message(av[2], ft_atoi(av[1]));
	return (EXIT_SUCCESS);
}
